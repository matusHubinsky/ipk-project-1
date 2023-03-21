## Vesion 1.0.0

### New Features
- TCP: read message from socket only by one byte at the time
- UDP: after sending a message, wait for 1 second. After no reply, send message again

### Known Problems
- program will not end communication properly after recieving ^C on stdin

## Vesion 1.0.1
### New Features
- TCP: 
- UDP: fixed infinite waiting after resending message 

### Known Problems
- program will not end communication properly after recieving ^C on stdin
- udp resend message is not tested