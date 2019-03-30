# All things displays and monitors
## Dealing with multiple monitors
Use `xrandr`
* Notes/issues: 
  * Random artifacts may occur if the frame buffer is incorrectly sized
    * The command will return a warning message. Example:
      * `xrandr: specified screen 6720x2080 not large enough for output HDMI-0 (3840x2160+0+0)`
  * Random artifacts may occur if xrandr conflicts with the display driver
    * No resolution has been determined for this
* Usage example
  * Situation
    * After calling `xrandr`, the following information is gathered
    * External display at HDMI-0 is 1920x1080; we want this to be the left display, at 2x scale
    * Internal display at eDP is 2880x1800; we want this to be the right display, at 1x scale
  * Calculations for frame buffer:
    * x: 1920*2 + 2880 = 6720
    * y: max(1080*2, 1800) = 2160
  * The command:
    * `xrandr --output HDMI-0 --scale 2x2 --mode 1920x1080 --fb 6720x2160 --pos 0x0; xrandr --output eDP --pos 3840x0`
