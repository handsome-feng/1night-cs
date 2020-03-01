---
title: How can I help
---

### Preparation

sudo apt install how-can-i-help

sudo apt install command-not-found

Generic instructions: https://mentors.debian.net/intro-maintainers
Reintroducing packages: https://www.debian.org/doc/manuals/developers-reference/ch05.en.html#reintroducing-pkgs



### Report Bug

```
sudo apt install python3-gi-cairo gir1.2-vte-2.91
reportbug --ui gtk2
```



### The experimental repository

```
deb http://deb.debian.org/debian experimental main
apt-get update
apt-get -t experimental install packagename

//listing all packages installed from experimental
aptitude search ~S~i~Aexperimental
```



### Debian version numbering

 The format is: [epoch:]upstream_version[-debian_revision]

The three components here are:

- epoch
  This is a single (generally small) unsigned integer. It may be omitted, in which case zero is assumed. If it is omitted then the upstream_version may not contain any colons. It is provided to allow mistakes in the version numbers of older versions of a package, and also a package's previous version numbering schemes, to be left behind.
- upstream_version
  This is the main part of the version number. It is usually the version number of the original ("upstream") package from which the .deb file has been made, if this is applicable. Usually this will be in the same format as that specified by the upstream author(s); however, it may need to be reformatted to fit into the package management system's format and comparison scheme.
  The comparison behavior of the package management system with respect to the upstream_version is described below. The upstream_version portion of the version number is mandatory.
  The upstream_version may contain only alphanumerics[36] and the characters "." (full stop), "+" (plus), "-" (hyphen), ":" (colon), "~" (tilde) and should start with a digit. If there is no debian_revision then hyphens are not allowed; if there is no epoch then colons are not allowed.
- debian_revision
  This part of the version number specifies the version of the Debian package based on the upstream version. It may contain only alphanumerics and the characters "." (full stop), "+" (plus), "~" (tilde) and is compared in the same way as the upstream_version is.
  It is optional; if it isn't present then the upstream_version may not contain a hyphen. This format represents the case where a piece of software was written specifically to be a Debian package, where the Debian package source must always be identical to the pristine source and therefore no revision indication is required.
  It is conventional to restart the debian_revision at 1 each time the upstream_version is increased.
  The package management system will break the version number apart at the last hyphen in the string (if there is one) to determine the upstream_version and debian_revision. The absence of a debian_revision is equivalent to a debian_revision of 0.
- Comparison
  When comparing two version numbers, first the epoch of each are compared, then the upstream_version if epoch is equal, and then debian_revision if upstream_version is also equal. epoch is compared numerically. The upstream_version and debian_revision parts are compared by the package management system using the following algorithm:
  The strings are compared from left to right.
  First the initial part of each string consisting entirely of non-digit characters is determined. These two parts (one of which may be empty) are compared lexically. If a difference is found it is returned. The lexical comparison is a comparison of ASCII values modified so that all the letters sort earlier than all the non-letters and so that a tilde sorts before anything, even the end of a part. For example, the following parts are in sorted order from earliest to latest: ~~, ~~a, ~, the empty part, a.
  Then the initial part of the remainder of each string which consists entirely of digit characters is determined. The numerical values of these two parts are compared, and any difference found is returned as the result of the comparison. For these purposes an empty string (which can only occur at the end of one or both version strings being compared) counts as zero.
  These two steps (comparing and removing initial non-digit strings and initial digit strings) are repeated until a difference is found or both strings are exhausted.
  Note that the purpose of epochs is to allow us to leave behind mistakes in version numbering, and to cope with situations where the version numbering scheme changes. It is not intended to cope with version numbers containing strings of letters which the package management system cannot interpret (such as ALPHA or pre-), or with silly orderings.

ubuntu will indicate that the package has been built specifically for Ubuntu. The alpha and build strings don't seem to have any particular meaning, but dfsg refers to a package that has been modified for compliance with the Debian Free Software Guidelines.



### Prepare patches for Debian package

#### 1. Retrieve the source package and install build-dependencies

The first step is to retrieve the latest version of the source package and to install the required build-dependencies. 

If you prefer, you can use dget (from the devscripts package) to directly grab the source package. You can find the URL of the .dsc files in the Package Tracking System for example.

 you can use debcheckout to retrieve the VCS repository instead (provided that you have the corresponding VCS installed):

```
$ debcheckout wordpress
declared git repository at git://git.debian.org/git/collab-maint/wordpress.git
git clone git://git.debian.org/git/collab-maint/wordpress.git wordpress ...
Cloning into wordpress...
```

It’s also a good idea to install the package “packaging-dev”. It's a meta-package depending on the most common tools that are used for Debian packaging work.



#### 2. Do the changes
Execute dch --nmu to record the fact that you’re working on an update prepared by someone who is not the maintainer (NMU means Non Maintainer Upload). This also ensures that if we build the package, we won't overwrite the original source package that we downloaded, thus making it possible to generate a "diff" between both versions.

##### 2.1. Modify Debian packaging files
Now fire your text editor and do the required changes in the “debian” sub-directory. You will probably run dch -a multiple times to document each subsequent change.

##### 2.2. Modify upstream files
If you have to modify upstream files, the proper way to do it depends on the source package format (“1.0” vs “3.0 (quilt)” vs “3.0 (native)”, see the debian/source/format file) and on the presence or not of a patch system (the what-patch can help you identify it). In this explanation, I’ll assume that the package is using the recommended format: “3.0 (quilt)”. (It also works for “1.0” if quilt is used and if you configured ~/.quiltrc as recommended by /usr/share/doc/quilt/README.source).

First you should ensure that all patches have been applied with quilt push -a. If there’s no patch yet, you want to create the debian/patches directory (with mkdir debian/patches). Note that you should better invoke quilt from the root of the source package (and the examples below assume this).

###### 2.2.1 Import a patch
If the upstream changes are already in a patch file (say /tmp/patch that you downloaded from the upstream VCS repository) you can import that patch like this:

$ quilt import -P fix-foobar.patch /tmp/patch
Importing patch /tmp/patch (stored as fix-foobar.patch)
$ quilt push
Applying patch fix-foobar.patch
[...]
Now at patch fix-foobar.patch
The -P option allows to select the name of the patch file created in debian/patches/. As you see, the new patch file is recorded in debian/patches/series but not applied by default, we’re thus doing it with quilt push.

###### 2.2.2. Create a new patch
If the upstream changes that you want to make are not in a patch yet, you should tell quilt that you’re going to create one:

$ quilt new fix-foobar.patch
Patch fix-foobar.patch is now on top
Then you must record every file that you’re going to modify with a quilt add invocation. quilt then makes a backup of those files so that it can generate the patch later on. If you’re going to modify the files with your text editor you can just do quilt edit file-to-modify, it’s the same than quilt add file-to-modify followed by sensible-editor file-to-modify.

$ quilt edit foobar.c
File foobar.c added to patch fix-foobar.patch
The last step is tell quilt to generate the patch:

$ quilt refresh
Refreshed patch fix-foobar.patch

###### 2.2.3 Patch Headers

We recommend that you tag every patch with [DEP-3](http://dep.debian.net/deps/dep3/) headers by putting them at the top of patch file. Here are some headers that you can use:

**Description**:	Description of what the patch does. It is formatted like Description field in debian/control: first line is short description, starting with lowercase letter, the next lines are long description, indented with a space.
**Author**:	Who wrote the patch (i.e. “Jane Doe <packager@example.com>”).
**Origin**:	Where this patch comes from (i.e. “upstream”), when Author is not present.
Bug-Ubuntu:	A link to Launchpad bug, a short form is preferred (like https://bugs.launchpad.net/bugs/XXXXXXX). If there are also bugs in upstream or Debian bugtrackers, add Bug or Bug-Debian headers.
**Forwarded**:	Whether the patch was forwarded upstream. Either “yes”, “no” or “not-needed”.
**Last-Update**:	Date of the last revision (in form “YYYY-MM-DD”).

#### 3. Test your changes
You should build your modified package with “debuild -us -uc”. You can easily install the resulting package with “debi”. Verify that everything works as expected. If not, continue your modifications until you’re satisfied with the result.

#### 4. Generate a patch and mail it
If you followed the instructions, you should have two .dsc files in the parent directory, like this:

```
$ cd ..
$ ls wordpress_*.dsc
../wordpress_3.0.5+dfsg-1.1.dsc
../wordpress_3.0.5+dfsg-1.dsc
```


Generating the patch to send to the maintainer is then just a matter of running debdiff:

```
$ debdiff wordpress_3.0.5+dfsg-1.dsc wordpress_3.0.5+dfsg-1.1.dsc >/tmp/wp-debdiff
```

You can send the /tmp/wp-debdiff file to the wordpress maintainer. Usually you send it via the bugreport that your update is fixing and you add the "patch" tag to the report.

This can be automated with the nmudiff utility. By default it assumes that you’re using mutt but it can also directly feed the resulting mail to sendmail. The default text that nmudiff proposes assumes that you’re actually performing an NMU and that the result has been uploaded. If that’s not the case, you should edit the text and make it clear that you're just sending a patch.

Tag the bug as "patch available" by running

```
bts tags [bugnumber] + patch
```

