<https://wiki.debian.org/Keysigning>

private key: 

* decrypt emails sent to you
* digitally sign emails

public key:

* send you encrypted mail
* verify emails you send.



revocation certificate:

What happens if you lose access to a secret [key![img](https://ssd.eff.org/sites/all/themes/ssd/img/info.png)](https://ssd.eff.org/en/glossary/key), or it stops being secret? A [revocation certificate![img](https://ssd.eff.org/sites/all/themes/ssd/img/info.png)](https://ssd.eff.org/en/glossary/revocation-certificate) is a file that you can generate that announces that you no longer trust that key. You generate it when you still have the secret key, and keep it for any future disaster.