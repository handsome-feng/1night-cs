---
title: Debian Maintainer
---

## Becoming a Debian Maintainer

### Identification

* generate a strong (>=2048) RSA GnuPG key.

* Send the fingerprint to DD to sign it. 

* Import the key received from DD:

  `$ gpg --import handsome_feng(B43C0E3B\)–Public.asc`

* Confirm the key signed success:

  `$ gpg --recv-key DD_public_key_ID`

  `$ gpg --list-sigs

* Update the key by send it to the key server.

  `$ gpg --keyserver pool.sks-keyservers.net --send-key 2811C825B43C0E3B`

### Declaration of intent

* Subscribe to the debian-devel-announce mailing list

* Ensure that GnuPG uses SHA2 signatures (in preference to SHA1); an example is having the following content in ~/.gnupg/gpg.conf:

  ```
  personal-digest-preferences SHA512
  cert-digest-algo SHA512
  default-preference-list SHA512 SHA384 SHA256 SHA224 AES256 AES192 AES CAST5 ZLIB BZIP2 ZIP Uncompressed
  ```

* Register for a Salsa account

* Register for a New Members account.

  * emailing  sso@rt.debian.org (Don't forget to sign your emil)

    ```
    To: sso@rt.debian.org
    Subject: [Debian RT] SSO Account for _____
    
    Please create a SSO Account for me.
    
    Account name: _____-guest
    Reason account is needed: _____
    OpenPGP key fingerprint: _____
    
    Thanks.
    ```

  * After receive the debsso account, use the Alioth icon on the right hand side at https://sso.debian.org to login.

  * Open https://sso.debian.org/alioth/certs/enroll_csr/ to get certificate.

    ```shell
    $ openssl genrsa -out handsome_feng-guest@users.alioth.debian.org.key 2048
    $ openssl req -new -sha256 -key handsome_feng-guest@users.alioth.debian.org.key -batch
    
    # Paste the CSR and click the 'Get certificate' button to get the handsome_feng-guest@users.alioth.debian.org.crt
    
    # Authenticate access via curl
    $ curl --key handsome_feng-guest@users.alioth.debian.org.key --cert handsome_feng-guest@users.alioth.debian.org.crt https://sso.debian.org/ca/test/env
    
    # Combine key and certificate in a pkcs12 file that can be imported in browsers (Type the password for the export, PS: such as your login password)
    $ openssl pkcs12 -export -out handsome_feng-guest@users.alioth.debian.org.p12 -inkey handsome_feng-guest@users.alioth.debian.org.key -in handsome_feng-guest@users.alioth.debian.org.crt
    ```

  * Import the xx.p12 from the certificate dialog at chrome://settings/certificates or from the command line with:

    ```
    pk12util -i handsome_feng-guest@users.alioth.debian.org.p12 -d sql:$HOME/.pki/nssdb
    ```

  * Then you can login the https://nm.debian.org/

* 

### reference

https://wiki.debian.org/DebianSingleSignOn

https://wiki.debian.org/Keysigning

https://wiki.debian.org/DebianMaintainer