# Solarize Police Pursuits

[![sampctl](https://img.shields.io/badge/sampctl-solar--pp-2f2f2f.svg?style=for-the-badge)](https://github.com/Se8870/solar-pp)

Solarize Police Pursuit, used for educational purposes only and learning path how to make stuff.
Original purposes was for our server april fools joke but i guess i kinda want to release this.

## Features
- [x] built from scratch
- [x] Lobby system
- [ ] Login/Register system
- [x] Core game functions
    - [x] Add team system
    - [x] Spreading each player to corresponding group
    - [x] Watching fights
    - [x] Finisher  
- [ ] A database system

There is plenty of implementations that i need to do but i guess you can help implementing one.

## Installation

Simply install to your project:

```bash
git clone git@github.com:Se8870/solar-pp.git
```

Ensure it using the following command:
```bash
sampctl ensure
```

And run it!

## How to contribute
You can simply clone this feature, go to your own branch and push it from there.

NOTE: NEVER PUSH DIRECTLY TO `master` BRANCH, MAKE YOUR OWN BRANCH AND MAKE PULL REQUEST!

## Directory meanings
* `core` - Folder utama game, hal-hal penting ada disana semua
* `utils` - Folder utilitas, lebih mengarah ke fungsi fungsi opsional yang tidak terlalu penting

## Coding styles

```pawn
#if defined _inc_include
    #undef _inc_include
#endif
 
#if defined _inc_include_included
    #endinput
#endif

#define _inc_include_included

// Disini bisa buat fungsi utamanya
GetPlayerFollower(playerid)
{
    // Selalu pakai guard clause untuk menghindari sphagetti code.
    if (false)
        return // something.
    // ...
}

// Hook paling bawah
#include <YSI_Coding\y_hooks>
hook OnPlayerConnect(playerid)
{
    // Pake indent style Allman, no K&R
}
```

## Testing

To test, simply run the package:

```bash
sampctl run
```
