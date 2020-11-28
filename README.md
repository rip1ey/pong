## Pong

  This a Pong clone written using C++ and SDL2.

### Building

  This project requires the `SDL2` library for the graphics and
  the `SDL_TTF` library for font rendering.

  Additionally, `cmake` is needed for building the project.
  The makefile is located in the root of the repo, so calling
  `make` from the `pong` directory will compile the project and
  place the compiled `pong` executable in the `output` directory.
  Running `make clean` will remove the `pong` executable, and the
  object files in the `src/obj` folder will be removed as well.

#### Output

```
  ~/Documents/projects/pong -> make
  g++ -c -o src/obj/Ball.o src/Ball.cpp -Isrc
  g++ -c -o src/obj/Paddle.o src/Paddle.cpp -Isrc
  g++ -c -o src/obj/PlayingField.o src/PlayingField.cpp -Isrc
  g++ -c -o src/obj/Pong.o src/Pong.cpp -Isrc
  g++ -o output/pong src/obj/Ball.o src/obj/Paddle.o src/obj/PlayingField.o src/obj/Pong.o -lSDL2 -lSDL2_ttf
  ~/Documents/projects/pong -> make clean
  rm src/obj/Ball.o src/obj/Paddle.o src/obj/PlayingField.o src/obj/Pong.o output/pong
```

### References

#### Font

  The font used to display the score was created by Petyka and
  can be downloaded from [dafont](https://www.dafont.com/retro-computer.font).
  Additionally, it can be found within the `font` directory as part of
  this repo.
