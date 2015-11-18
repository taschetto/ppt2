require './lita_rpi'

Lita.configure do |config|
  config.robot.name = "Lita"
  config.robot.adapter = :slack
  config.adapters.slack.token = "xoxb-13997161842-W89rKQer106MkwaweNNYj8KY"
end
