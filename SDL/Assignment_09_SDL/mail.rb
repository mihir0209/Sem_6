require 'mail'

Mail.defaults do
delivery_method :smtp, {
:address => 'smtp.gmail.com',
:port => 587,
:user_name => 'ritasdeva81@gmail.com',
:password => 'ezdy qtmg asqk oxlt', #I've already deleted my password from Google account...😂
:authentication => :login,
:enable_starttls_auto => true
}
end

message = Mail.new do
from 'ritasdeva81@gmail.com'
to 'kartavyaparhate1704@gmail.com'
subject 'Kartavya Parhate on fire'
body 'The body is cold'
end

message.deliver!