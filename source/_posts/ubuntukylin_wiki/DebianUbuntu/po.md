![gettext](../../pics/gettext.svg "Typical gettext workflow")





```shell
for po in `ls *.po`; do msgmerge -U $po slideshow-ubuntukylin.pot; done
```

