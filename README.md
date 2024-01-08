# backctl

## Table of Contents
> [What is `backctl`?](#what-is-backctl) \
> [Why `backctl` over `xbacklight`?](#why-backctl-over-xbacklight) \
> [Installing](#installing) \
> [Usage](#usage) \
> [LICENSE](#license)

---

## What is `backctl`?
`backctl` is a backlight control program for Linux, inspired by `xbacklight` and written out of frustration of
using `xbacklight`. `backctl` is a program that aims to be a drop-in replacement for `xbacklight` for users that
have an AMD Backlight device, Wayland users or users that simply just prefer to use the TTY on their device, but
don't want the constant full brightness of their screen.

`backctl` is written in C++, with the same philosophy as the Suckless utilities, such as `st`, `dmenu`, `slock`
etc. This philosophy is that the user can add functionality by simply modifying the source code. That's one of
the goals with this tool.

## Why `backctl` over `xbacklight`
`xbacklight`, much like the rest of the `x`-tools have the issue of being old and not that great. For example,
the `xbacklight` utility is Xorg specific and doesn't have support for AMD backlight devices. `backctl` however
simply modifies the `/sys/class/backlight/*/brightness` file. This means that it works regardless of the display
system used - Xorg, Wayland or even the tty.

`backctl` also aims to be a drop-in replacement for `xbacklight`, and as such the primary commands to change
the brightness and get brightness are the exact same as they are for `xbacklight`. This was done so that scripts
that use `xbacklight` don't break should the user decide to switch to this tool.

## Installing
To install `backctl`, you need to have a working C++ compiler installed, and GNU Make. These should be available
in your distribution as one of the following:

**Debian/Ubuntu/Mint or any other `deb` based distro**
```
sudo apt install build-essential
```

**Arch/Artix/Manjaro or any other `pacman` based distro**
```
sudo pacman -S base-devel
```

Once you have these installed, you can simply run

```
make
sudo make install
```

Once it's installed, it is recommended to add this to your **sudoers** file, just so that you can modify the display
brightness without needing to put your sudo password in:

```
%wheel ALL=(ALL:ALL) NOPASSWD: /usr/local/bin/backctl
```

### Arch Users
Arch users can install `backctl` via the AUR:

```
git clone https://aur.archlinux.org/backctl-git.git
cd backctl-git
makepkg -si
```

## Usage
```
___.                  __           __  .__
\_ |__ _____    ____ |  | __ _____/  |_|  |
 | __ \\__  \ _/ ___\|  |/ // ___\   __\  |
 | \_\ \/ __ \\  \___|    <\  \___|  | |  |__
 |___  (____  /\___  >__|_ \\___  >__| |____/
     \/     \/     \/     \/    \/

FLAG                                    DESCRIPTION
==============================================================================

-inc <VALUE> | + <VALUE>                Increase backlight by VALUE
-dev <VALUE> | - <VALUE>                Decrease backlight by VALUE
-get         | -g                       Get the current backlight value
-get-perc    | -gp                      Get the current brightness as a percentage
--help       | -h                       Show this help text
--version    | -v                       Display the current backctl version
```

## LICENSE
Copyright (C) 2024	Rebecca White <rtw@null.net>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
