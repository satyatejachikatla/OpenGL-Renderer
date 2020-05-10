# OpenGL Basic Renderer

Created a opengl based renderer for rendering simple objects. <br>
![Sphere](https://github.com/turrentrock/OpenGL-Renderer/blob/master/res/pictures/earth.png)
![Stall](https://github.com/turrentrock/OpenGL-Renderer/blob/master/res/pictures/stall.png)
### Resources:
- [OpenGl serier by The Cherno](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)
- [ThinMatrix](https://www.youtube.com/watch?v=VS8wlS9hF8E&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP)
- [LearnOpenGl](https://learnopengl.com/)
- [The Art of Coding](https://www.youtube.com/watch?v=il_Qg9AqQkE)

### Screen capture using ffmpeg
```
ffmpeg -video_size 900x1000 -framerate 25 -f x11grab -i $DISPLAY.0+100,52 output.mp4
ffmpeg -i output.mp4 -vf "fps=10,scale=320:-1:flags=lanczos" -c:v pam -f image2pipe - | convert -delay 10 - -loop 0 -layers optimize output.gif
```