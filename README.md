# FDF - @42Born2Code

A 3D wireframe rendering engine.

### What is FdF?

[FdF][1] is the first project of the graphic branch at [42][2] that requires us to create a simplified 3D graphic representation of a landscape.

![](https://github.com/jon-finkel/fdf/blob/master/fdf.gif)

### Installation

`cd libft ; git submodule init ; git submodule update ; cd .. ; make`

### Features

- Isometric projection
- Camera rotation
- Zoom
- Translation
- Clipping
- Buffered render
- Cinema mode

Controls:
- `+`: zoom in
- `-`: zoom out
- `A/S/D/W`: move left / down / right / up
- `E`: increase move speed
- `Q`: decrease move speed
- `^/v`: rotation on X-axis
- `</>`: rotation on Y-axis
- `Z/C`: rotation on Z-axis
- `0`: enable / disable cinema mode
- `1/2`: decrease / increase X-axis rotation speed for cinema mode
- `3/4`: decrease / increase Y-axis rotation speed for cinema mode
- `5/6`: decrease / increase Z-axis rotation speed for cinema mode
- `7/8/9`: stop rotation on X/Y/Z-axis for cinema mode
- `alt`: enable / disable psych mode

### Final Mark

`125/100 (MAX GRADE)`

[1]: https://github.com/jon-finkel/fdf/blob/master/projects_instructions/fdf.en.pdf "FdF PDF"
[2]: http://42.fr "42 Paris"
