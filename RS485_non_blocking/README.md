# RS485_non_blocking

A non-blocking library for sending information between Arduinos connected via RS485 wiring as described [here](https://www.gammon.com.au/forum/?id=11428).

A blocking version is available at https://github.com/nickgammon/RS485_protocol

The protocol is the same, but it lets you handle an incoming packet a byte at a time. This could be handy where you have multiple incoming devices.


## Sending sketch


```c++
#include <RS485_non_blocking.h>

size_t fWrite (const byte what)
{
  return Serial.write (what);  
}

RS485 myChannel (NULL, NULL, fWrite, 0);

void setup ()
{
  Serial.begin (115200);
  myChannel.begin ();
}  // end of setup

const byte msg [] = "Hello world";

void loop ()
{
  myChannel.sendMsg (msg, sizeof (msg));
  delay (1000);   
}  // end of loop
```


There is now a RS485 class (which I made an instance of called myChannel). You supply in the constructor a "read", "available" and "write" callback. If you are only writing you don't need the read or available callbacks, as illustrated above. You also supply a maximum buffer length (this only applies for reading).

## Receiving sketch


```c++
#include <RS485_non_blocking.h>

 int fAvailable ()
   {
   return Serial.available ();  
   }
 
 int fRead ()
   {
   return Serial.read ();  
   }
 

RS485 myChannel (fRead, fAvailable, NULL, 20);

void setup ()
  {
  Serial.begin (115200);
  myChannel.begin ();
  }  // end of setup

void loop ()
  {
  if (myChannel.update ())
    {
    Serial.write (myChannel.getData (), myChannel.getLength ()); 
    Serial.println ();
    }
  }  // end of loop
```


In this sketch the loop function calls myChannel.update () which gradually assembles the incoming packet into a buffer inside the class instance. You need to call myChannel.begin () in setup to actually allocate the required amount of memory for it.

Once myChannel.update () returns true, a packet is ready, and you can then access its data, and the length of its data.

There are some other functions in the class which tell you whether a packet is in progress, when it started, how many errors have occurred, and so on.
