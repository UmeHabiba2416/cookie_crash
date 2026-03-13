```
 ██████╗ ██████╗  ██████╗ ██╗  ██╗██╗███████╗     ██████╗██████╗  █████╗ ███████╗██╗  ██╗
██╔════╝██╔═══██╗██╔═══██╗██║ ██╔╝██║██╔════╝    ██╔════╝██╔══██╗██╔══██╗██╔════╝██║  ██║
██║     ██║   ██║██║   ██║█████╔╝ ██║█████╗      ██║     ██████╔╝███████║███████╗███████║
██║     ██║   ██║██║   ██║██╔═██╗ ██║██╔══╝      ██║     ██╔══██╗██╔══██║╚════██║██╔══██║
╚██████╗╚██████╔╝╚██████╔╝██║  ██╗██║███████╗    ╚██████╗██║  ██║██║  ██║███████║██║  ██║
 ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝╚══════╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝
```

<div align="center">

🍪 **Match. Swap. Crash. Repeat.** 🍪

*A gravity-powered match-3 browser game — no installs, no nonsense, just cookies.*

[![Play Now](https://img.shields.io/badge/▶%20Play%20Now-Open%20in%20Browser-facc15?style=for-the-badge&labelColor=1a0a2e)](cookie_crash.html)
[![Version](https://img.shields.io/badge/Version-1.0.0-ec4899?style=for-the-badge&labelColor=1a0a2e)](.)
[![License](https://img.shields.io/badge/License-MIT-4ade80?style=for-the-badge&labelColor=1a0a2e)](.)
[![Zero Dependencies](https://img.shields.io/badge/Dependencies-Zero-3b82f6?style=for-the-badge&labelColor=1a0a2e)](.)

</div>

---

## 🌌 What Is This?

Somewhere between a bakery and a black hole, **Cookie Crash** was born.

It started as a C++ OpenGL experiment — raw pixels, raw frustration, raw fun. Then it evolved into a sleek, zero-dependency browser game that runs anywhere HTML does. You swap colorful cookies, create matches of 3 or more, and watch gravity pull everything down in a beautiful cascade of chaos.

**You have 60 seconds. Make them count.**

---

## 🎮 How to Play

```
┌─────────────────────────────────────────────────────┐
│                                                     │
│   1. 👆  Click any cookie to SELECT it              │
│                                                     │
│   2. 👆  Click an ADJACENT cookie to SWAP them      │
│                                                     │
│   3. 💥  Match 3 or more in a row/column = POINTS   │
│                                                     │
│   4. 🌊  Gravity pulls cookies DOWN automatically   │
│                                                     │
│   5. ⛓️  Chain reactions = BONUS POINTS              │
│                                                     │
│   6. ⏱️  60 seconds on the clock — GO!              │
│                                                     │
└─────────────────────────────────────────────────────┘
```

> **Pro tip:** Invalid swaps (ones that don't create a match) are automatically reversed. No penalty — the game's fair like that.

---

## 🍪 The Cookie Roster

| Cookie | Color | Vibe |
|--------|-------|------|
| 🔴 | Crimson | Bold. Fearless. Goes first. |
| 🟢 | Emerald | Cool, calm, always in the mix. |
| 🔵 | Cobalt | Rare. Mysterious. Worth chasing. |
| 🟡 | Amber | Sweet like honey. Sneaks up on you. |
| 🩷 | Magenta | The wildcard. Pure chaos energy. |

---

## ✨ Features

- **🧠 Smart swap detection** — only valid moves are accepted; invalid swaps undo themselves instantly
- **🌊 Real gravity** — cookies fall from above to fill gaps, just like the original C++ version
- **⛓️ Chain reactions** — matches trigger more matches, combos rack up automatically
- **⭐ Score system** — +10 points per matched cookie, chains multiply the madness
- **🏆 Best score tracking** — persists across rounds within your session
- **⏱️ Countdown timer** — color-coded bar goes green → yellow → red as time runs out
- **💫 Score popups** — satisfying floating "+points" every time you clear a combo
- **🚫 Zero dependencies** — pure HTML + CSS + JavaScript, no libraries, no frameworks

---

## 🚀 Getting Started

It could not be simpler:

```bash
# Step 1: Download cookie_crash.html
# Step 2: Open it in a browser
# Step 3: There is no step 3
```

Or if you're feeling fancy:

```bash
# Serve locally with Python
python -m http.server 8080

# Then open:
# http://localhost:8080/cookie_crash.html
```

**Compatibility:** Any modern browser. Chrome, Firefox, Safari, Edge — all welcome at the cookie party.

---

## 🏗️ Architecture

```
cookie_crash.html
│
├── 🎨 CSS Layer
│   ├── Deep space background (radial gradients + star dots)
│   ├── Cookie cells (hover, selected, clearing, falling states)
│   ├── Animated score popups
│   └── Game-over overlay
│
├── 🧩 HTML Layer
│   ├── Stats bar (Score / Timer / Best)
│   ├── Animated timer bar
│   ├── 10×10 grid container
│   └── Game-over overlay with restart button
│
└── ⚙️ JS Engine
    ├── initGrid()          → fills 10×10 grid, resolves starting matches
    ├── resolveInitialMatches() → prevents matches on load
    ├── findMatches()       → horizontal + vertical 3+ detection
    ├── applyGravity()      → drops cookies, spawns new ones from top
    ├── processMatches()    → recursive cascade handler with animation
    ├── onCellClick()       → selection + swap + validation logic
    ├── renderGrid()        → DOM render with optional fall animation
    ├── startTimer()        → interval countdown with visual bar
    └── startGame()         → full reset and game init
```

---

## 📊 Scoring

```
Match 3  →  30 points
Match 4  →  40 points
Match 5  →  50 points
Match N  →  N × 10 points

Cascade bonus: each wave of matches scores independently.
Stack cascades for maximum cookie carnage.
```

---

## 🧬 Origin Story

This game began as a **C++ / OpenGL desktop application** using GLEW and FreeGLUT:

```cpp
// The OG grid — 10×10, rendered with raw OpenGL calls
void DrawCircle(float x, float y, float r, float* c) {
    glColor3fv(c);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i += 10)
        glVertex2f(x + r*cos(i*M_PI/180), y + r*sin(i*M_PI/180));
    glEnd();
}
```

The web version keeps the same **core logic** — identical grid dimensions, the same gravity algorithm, the same match detection — just translated from C++ to JavaScript and dressed up for the browser age.

---

## 📁 File Structure

```
cookie-crash/
│
├── 📄 cookie_crash.html     ← The entire game (single file!)
└── 📄 README.md             ← You are here 👈
```

Yes, it's a **single file**. The whole game. All of it. One HTML file.

---

## 🛠️ Customization

Want to tweak the game? All config lives at the top of the `<script>` tag:

```javascript
const ROWS = 10;        // Grid height
const COLS = 10;        // Grid width
const GAME_TIME = 60;   // Seconds per round

function rand5() {
  return Math.floor(Math.random() * 5); // Number of cookie types (currently 5)
}
```

Want to add a 6th cookie color? Add a `.cookie-5` CSS rule and change `rand5()` to `rand6()`. It's that clean.

---

## 🤝 Contributing

Found a bug? Have an idea? Pull requests welcome!

```
Things that would be awesome:
  □ High score leaderboard (localStorage)
  □ Special cookies (bomb, rainbow, row-clear)
  □ Difficulty levels (more colors = harder)
  □ Sound effects
  □ Mobile touch support
  □ Combo multiplier display
```

---

## 📜 License

**MIT** — do whatever you want with it. Bake it into your project, sell it, remix it, eat it. Just don't blame us if you lose three hours of your afternoon to it.

---

<div align="center">

Created by Um e Habiba

*"One more swap."  — everyone who has ever played this game*

</div>
