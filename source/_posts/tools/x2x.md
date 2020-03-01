x2x does exactly what you want:

```
$ ssh -X othermachine x2x -west -to :0
```

Now you can move your mouse to the left of your laptop and it wii appear in that other machine. Keyboard 'goes' there too.

You'll need to enable X forwarding in that other machine's sshd.