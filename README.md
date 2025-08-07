# 🎙️ pseudo-tts-engine

A playful, system-wide pseudo text-to-speech engine inspired by **Animal Crossing**'s iconic character "voices".

Whenever you press a key, the engine plays a corresponding sound file — creating a fun "talking" effect as you type. Perfect for creative projects, accessibility experiments, or just for adding a little personality to your system.

---

## ✨ Features

- 🎧 Plays a unique sound for each key press  
- 🌐 Captures global key events using `libuiohook`  
- 🔊 Asynchronous sound playback via `SDL2_mixer` (no lag)  
- 🗂️ Automatically creates the `sounds/` folder if missing  
- 💡 Platform-independent (works on **Linux**, **macOS**, and **Windows** with compatible libraries)  
- 🎮 Inspired by the speech effect in **Animal Crossing**

---

## 📁 Sound Files

- The included sound files are **in German** (`deutsch`).  
- Each file is named according to its key:  
  Examples: `a.mp3`, `space.mp3`, `1.mp3`, `f1.mp3`, etc.  
- You're **welcome to record your own custom sounds** — just keep the same filenames for compatibility.

🎤 Want your own voice? Record it! Keep clips short (50–300 ms) for the best effect.

---

## 🛠️ Requirements

- [`libuiohook`](https://github.com/kwhat/libuiohook) – for global key listening  
- [`SDL2`](https://www.libsdl.org/) – for audio handling  
- [`SDL2_mixer`](https://www.libsdl.org/projects/SDL_mixer/) – for playing sound files  
- POSIX-compatible system (**Linux**, **macOS**, or **Windows** via MinGW or MSYS2)  
- C compiler with pthread support

---

## 🧱 Installation

### 📦 Install Dependencies

**Debian/Ubuntu-based systems:**

```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-mixer-dev libuiohook-dev build-essential
```

### 🔨 Build the Program

```bash
gcc -o pseudo-tts-engine main.c -lSDL2 -lSDL2_mixer -luiohook -lpthread
```

---

## ▶️ Running the Program

```bash
./pseudo-tts-engine
```

- The program starts listening for key presses globally.  
- A matching sound will be played for every recognized key.  
- Press **Escape (ESC)** to safely exit the program.

---

## 🎵 Sound File Format

All sound files must be placed in the `sounds/` directory.

Supported keys include:

- **Letters**: `a.mp3`, `b.mp3`, ..., `z.mp3`  
- **Numbers**: `0.mp3` to `9.mp3`  
- **Special keys**: `space.mp3`, `enter.mp3`, `tab.mp3`, `backspace.mp3`, etc.  
- **Function keys**: `f1.mp3` to `f12.mp3`  
- **Symbols**: `comma.mp3`, `period.mp3`, `minus.mp3`, etc.

💡 Supported formats: `.mp3` or `.wav` (via SDL2_mixer)

---

## 🎤 Creating Your Own Voice

To replace or customize the voice:

1. Record short audio snippets for each key (e.g., with Audacity or your phone)  
2. Keep files short and punchy (recommended: 50–300 milliseconds)  
3. Save them using the correct filenames into the `sounds/` directory  

🔁 The program will automatically pick up your custom files without any code changes.

---

## 🐾 Inspiration

This project is inspired by the quirky, charming character speech in **Animal Crossing**, where characters "talk" using fast-paced phoneme-like tones that simulate spoken language.

`pseudo-tts-engine` brings that idea to your keyboard — making it sound like your system is speaking as you type.

---

## 📜 License

This project is licensed under the **MIT License**.  
Feel free to use, modify, and share it however you like.

---

Enjoy giving your system a unique voice! 🎉
