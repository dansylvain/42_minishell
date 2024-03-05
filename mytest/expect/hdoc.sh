#!/usr/bin/expect

set timeout 0

spawn sh -c "<<end <<end"
#spawn <<end <<end
after 100

expect ""
after 100

send "my here doque"
after 100

send "\r\x04"
after 100

expect ""
after 100
send "my here cat"
after 100

# Fin du script
expect eof

