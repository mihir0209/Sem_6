require 'mail'
# Set up SMTP settings
Mail.defaults do
delivery_method :smtp, {
:address => 'smtp.gmail.com',
:port => 587,
:user_name => 'ritasdeva81@gmail.com',
:password => 'bmlo vjbg dsld utaj',
:authentication => :login,
:enable_starttls_auto => true
}
end

# Define email message
message = Mail.new do
from 'ritasdeva81@gmail.com'
to 'mihirpatil128@gmail.com'
subject 'Hello from Ruby!'
body 'This is a test email sent from Ruby.'
end

# Send email
message.deliver!