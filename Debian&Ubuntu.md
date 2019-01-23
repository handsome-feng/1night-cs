本地准备工作:

~/.bashrc:

```
export DEBFULLNAME="handsome_feng"
export DEBEMAIL="jianfengli@ubuntukylin.com"
alias mylintian="lintian -i -EvIL +pedantic --verbose"
alias mylicensecheck="licensecheck -r . | grep -v 'UNKNOWN'"
```

~/.