require 'serialport'

class Array
  def chr
    self.map { |e| e.chr }
  end
end

module Lita
  module Handlers
    class RpiController < Handler

      route /temp/i, :temp, help: { "temp" => "Shows temperature." }
      route /all\s+leds\s+(on|off)/i, :all_leds, help: { "all leds (on|off)" => "Turns all leds ON or OFF." }
      route /led\s+(0|1|2|3)\s+(on|off)/i, :led, help: { "led (0|1|2|3) (on|off)" => "Turns a led ON or OFF." }

      def temp(response)
        response.reply `/opt/vc/bin/vcgencmd measure_temp`
      end

      def led response
        led = response.matches[0][0]
        value = response.matches[0][1]
        response.reply("Ok, #{response.user.name}! Gonna turn #{value} led #{led}! Just a moment!")

        SerialPort.open("/dev/ttyAMA0", 9600, 8, 1, SerialPort::NONE) do |tty|
          tty.sync = true
          tty.flush_output
          cmd = [0.to_i, led.to_i, value == "on" ? 1.to_i : 0.to_i, 13.to_i]
          tty.write(cmd.chr.join)
        end
      end

      def all_leds response
        value = response.matches[0][0]
        response.reply "Turn all leds #{value}? Consider it done, master #{response.user.name} ."

        SerialPort.open("/dev/ttyAMA0", 9600, 8, 1, SerialPort::NONE) do |tty|
          tty.sync = true
          tty.flush_output
          cmd = [2.to_i, 0.to_i, value == "on" ? 1.to_i : 0.to_i, 13.to_i]
          tty.write(cmd.chr.join)
        end
      end
    end

    Lita.register_handler(RpiController)
  end
end
