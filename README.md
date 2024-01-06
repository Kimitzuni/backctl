# backctl

## What is `backctl`?
`backctl` is a backlight controller program, inspired by `xbacklight`, but that avoids some of the
oddly specific things that `xbacklight` does, such as being Intel and Xorg specific.

## Why `backctl` over `xbacklight`?
`xbacklight` has a number of very odd issues, such as being Intel specific; in that it does not work
on AMD Backlight Devices. This is frustrating for me especially, as I have a laptop that has an AMD
backlight, and I cannot use `xbacklight` to change the brightness.

`xbacklight` is also Xorg specific, meaning that you need to be running Xorg at if you want to use
it, `backctl` is not Xorg specific, and instead just modifies the value in
`/sys/class/backlight/#/brightness` to change the backlight brightness. This has the added bonus of
being able to be ran within Xorg, Wayland and the tty.

`backctl` also takes the Suckless philosophy of tools in that to make a modification you edit the
source code instead of a configuration file. This has the bonus of it being lightweight.

`backctl` has also been written with compatibility with `xbacklight` in mind, this means that the
main functions use the same flags as `xbacklight`. This is so that scripts that are using
`xbacklight` don't break if the user decides to switch over to `backctl`
