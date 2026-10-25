# Pseudo TTS Engine

> Give every key press a short, character-like voice sound inspired by Animal Crossing.

![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)
![SDL2](https://img.shields.io/badge/audio-SDL2-blue)
![Vibe coded](https://img.shields.io/badge/development-vibe--coded-8A2BE2)

> **Vibe-coded project:** the idea, behavior, testing, and direction are mine; AI-assisted development was used to implement and refine parts of the project.

The program listens for global keyboard events through `libuiohook` and plays a matching file from `sounds/` asynchronously with SDL2_mixer.

## Features

- Global key detection
- Per-key `.mp3` or `.wav` samples
- Asynchronous playback
- Included German sound set
- Easy voice replacement through filename-based mapping

## Requirements

- A C compiler
- `libuiohook`
- SDL2 and SDL2_mixer
- POSIX threads

On Debian/Ubuntu-based systems:

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-mixer-dev libuiohook-dev
```

> Some distributions do not package `libuiohook-dev`; in that case, build and install libuiohook from its upstream repository.

## Build

```bash
git clone https://github.com/CopyPasteUser/Pseudo-TTS-Engine.git
cd Pseudo-TTS-Engine
gcc pseudoTTS.c -o pseudo-tts-engine -lSDL2 -lSDL2_mixer -luiohook -lpthread
```

## Run

```bash
./pseudo-tts-engine
```

Press `Esc` to stop the program.

## Custom sounds

Place short samples in `sounds/` using the names expected by the key mapping, for example:

```text
sounds/a.mp3
sounds/space.mp3
sounds/enter.mp3
sounds/f1.mp3
```

Clips around 50–300 ms work best. Keep the filename unchanged when replacing a voice sample.

## Privacy note

The application observes global key events to trigger sounds. It is intended for local personal use; inspect the source before running global input hooks.

## License

MIT — see [LICENSE](LICENSE).