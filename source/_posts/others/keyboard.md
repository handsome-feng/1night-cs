```
/*  
- date: 2016.11.24
- build: gcc fake_keyboard.cpp `pkg-config --cflags --libs x11 gtk+-3.0 xtst`
- */

#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#include <X11/extensions/XTest.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
gtk_init(&argc, &argv);
KeySym key = XK_Super_L;
GdkDisplay *gdk_display = gdk_display_get_default();
Display *display = gdk_x11_display_get_xdisplay(gdk_display);

int c;
int x = 0;
while((c=cin.get())!=EOF) {
    XTestFakeMotionEvent(display, 0, x++, 100, 0);
    XSync(display, False);
}

gtk_main();
return 0;
}
```

