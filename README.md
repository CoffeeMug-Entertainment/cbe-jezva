# CoffeeBean Engine 1 - Jezva
Simple engine, made in C++

## License

Engine code is released under the zlib license. Libraries come with their own licenses included. 

## Summary

Written by Fix:
This is my first ever game engine. I had many ideas for it, but ultimately I'm dragging all the baggage from when I knew less, and untangling all of that is proving more and more difficult to work with. So, I have just decided to build a second engine from scratch.

For smaller, simpler games like pong or breakout, this engine is amazing, and if you need a simple codebase to learn basic engine structure from, I can recommend you take a look in here!

There's an example Pong game in the examples folder, do take a look at that if you wish to use this.

For more serious dev, I recommend CoffeeBean 2 (Comming soon!).

## Contributing

If anyone wishes to contribute code, improve or port stuff, I'll be more than happy to accept PRs.

## Building

You can build it on Windows only using MinGW, as it's very much geared towards how things are done on Linux (primarily Arch).
For Linux, you're expected to have OpenAL and SDL2 (yeah, I flubbed the source inclusion with the thirdparty folder), and the rest is done through CMake
