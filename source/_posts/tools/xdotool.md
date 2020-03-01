xdotool getmouselocation 

My extra for sequential clicking into a few positions is a file positions.txt (given by a few eval/echo runs):

```sh
123 13
423 243
232 989
```

And the code that uses it is:

```sh
while read line; do
     X=`echo $line| cut -c1-3`; 
     Y=`echo $line| cut -c4-7`;
     xdotool mousemove --sync $((  0.5 + $X )) $(( 0.5 + $Y ));
     xdotool click 1
done < positions.txt
```

If there is no need to scale pixels (unlike my case), it could be a simple

```sh
while read line; do
     xdotool mousemove --sync $line;
     xdotool click 1
done < positions.txt
```