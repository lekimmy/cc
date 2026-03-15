*This project has been created as part of the 42 curriculum by **ls-phabm***

# Description

> the project, including its goal and a brief overview

### Project

Create my first basic computer graphics project.

### Goal

- Use the school’s graphical library, the MiniLibX -developed
internally and includes basic necessary tools to open a window, create images and deal with keyboard and mouse events.
- Use the mathematical concept of complex numbers
- Explore computer graphics optimization
- Practice event handling.

### Means

- The program has to display the image in a window.
   - Window management must remain smooth (e.g., switching to another window, minimizing, etc.).
   - Pressing ESC must close the window and quit the program in a clean way.
   - Clicking on the cross on the window’s frame must close the window and quit the program in a clean way.
- Offer Julia set, Mandelbrot set
   - Create different Julia sets by passing different parameters to
the program
   - Use at least a few colors to reveal the depth of each fractal (experiment with psychedelic effects bro)

Typical Mandelbrot bounds:
```
x_min = -2.0
x_max = 1.0
y_min = -1.5
y_max = 1.5
```
Typical Julia bounds:
```
x_min / ymin = -1.5
x_max / y_max = 1.5
```
Typical Tricorn bounds: (mine shows full symmetry with -2 ; 2)
```
x_min = -2.0
x_max = 1.0
y_min = -1.5
y_max = 1.5
```
Typical Burning Ship bounds:
```
x_min = -2.0
x_max = 1.5
y_min = -2
y_max = 1
```

Mandelbrot suite formula : `z(n+1) = z(n)^2 + c` 
- z and c are complex numbers i.e. x (real) + y (real) * i (imaginary)
- an imaginary number is i^2 = -1
- a fractal is a map in the complex plane (x, y) of the given suite
- each point within the fractal converges given a maximum number of iterations
- all others diverge before reaching that maximum number of iterations
- this project maps each one of them according to their escape velocity using color grading

Every other fractal is a variation of Mandelbrot :
- Mandelbrot : `z(n+1) = z(n)^2 + c` 
   - z starts at (0,0) and c is the pixel coordinate to the complex plane
- Julia : `z(n+1) = z(n)^2 + c` 
   - z is the pixel coordinate to the complex plane and c is a constant
- Tricorn : `z(n+1) = (conj(z(n)))^2 + c` negate z(n) before squaring in suite
   - z starts at (0,0) and c is the pixel coordinate to the complex plane
- Burning Ship :  `z(n+1) = (fabs(z(n)))^2 + c` absolute value of z(n) before squaring in suite
   - z starts at (0,0) and c is the pixel coordinate to the complex plane

### Constraints

- Global variables are forbidden.
- Use the MiniLibX library.
- A parameter is passed on the command line to define what type of fractal will be
displayed in a window.
   - You can handle more parameters to use them as rendering options.
   - If no parameter is provided, or if the parameter is invalid, the program displays a list of available parameters and exits properly.

### Bonus

- Offer additional fractals (Tricorn, Burning Ship)
- Zoom follows the actual mouse position.
- Navigation using the arrow keys.
- Make the color range shift.
- Dynamic Julia with mouse move + freeze motion with space key

# Instructions

> any relevant information about compilation, installation, and/or execution

1. Compile using `make`
2. Have fun with the different fractals
3. Zoom in & out with the mouse
4. Navigate the fractal using keyboard arrows
5. For Julia :
   - Hover the mouse to reshape it dynamically
   - Press `space` key to freeze mouse motion
   - Zoom in & out with the mouse
   - Press `space` key once more to unfreeze mouse motion 

Commands to execute program:

```
./fractol mandelbrot
./fractol tricorn
./fractol "burning ship"

./fractol julia 0 0 // circle
./fractol julia -0.8 0.156 // lightning
./fractol julia 0.285 0.01 // spirals
./fractol julia -0.4 0.6 // rabbit
./fractol julia -0.75 0.25 // cosmic
./fractol julia 0.3 0.5 // whirlwind

```

# Resources

> listing classic references related to the topic (documentation, articles, tutorials, etc.)
> a description of how AI was used — which tasks and which parts of the project.

- minilibX : 
   - tutorial [https://www.youtube.com/watch?v=ANLW1zYbLcs](https://www.youtube.com/watch?v=ANLW1zYbLcs)
   - events & masks [https://harm-smits.github.io/42docs/libs/minilibx/events.html](https://harm-smits.github.io/42docs/libs/minilibx/events.html)
- fractals : 
   - [https://en.wikipedia.org/wiki/Fractal](https://en.wikipedia.org/wiki/Fractal)
   - [https://www.youtube.com/watch?v=wUlVFYJIUNA](https://www.youtube.com/watch?v=wUlVFYJIUNA)
- fractol : 
   - tutorial [https://www.youtube.com/watch?v=ANLW1zYbLcs](https://www.youtube.com/watch?v=ANLW1zYbLcs)
- funcheck : <https://github.com/froz42/funcheck>
- Markdown : [https://www.markdownguide.org/cheat-sheet/](https://www.markdownguide.org/cheat-sheet/)

AI was used to break down the logic behind the maths (divergence), color grading (bit shifting vs. hex), improve performance (operations & impact on CPU calculations, state & event handling, max iter according to zoom factor, frame throttling for rendering) and build up a custom Bash tester.
