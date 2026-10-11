# BubbleGlass Screensaver

A transparent, animated soap-bubble screensaver for Windows 11 using Windhawk.

BubbleGlass displays colorful, iridescent soap bubbles directly above the live Windows desktop after a configurable period of inactivity. The desktop remains visible underneath because the saver uses a transparent layered window with per-pixel alpha blending.

The renderer targets smooth **60 FPS** animation and is designed to work well on large and multi-monitor desktop surfaces.

## Preview

![BubbleGlass Screensaver preview](https://i.imgur.com/Nh5EyFe.png)

![BubbleGlass Screensaver animated preview](https://i.imgur.com/gCsmdj6.gif)

*Transparent, animated soap bubbles move across the live Windows desktop while the desktop remains visible underneath. The optional diagnostics overlay shows real-time FPS, frame time, jitter and rendering performance.*

## Features

- Transparent screensaver displayed directly above the live Windows desktop.
- Smooth 60 FPS animation target.
- Per-pixel transparency using a layered Windows window.
- Colorful thin-film iridescent bubble rendering.
- Animated rainbow interference colors.
- Multiple configurable bubble sizes.
- Gradual bubble spawning instead of filling the screen instantly.
- Natural drifting motion.
- Optional air-current / turbulence simulation.
- Bubble-to-bubble collision physics.
- Optional wall bouncing or screen-edge wrapping.
- Configurable bubble lifetime and animated popping.
- Adjustable opacity, desktop dimming and subtle shadows.
- Multi-monitor support.
- Configurable mouse-movement dismissal threshold.
- `Print Screen` is allowed through with a short grace period for Snipping Tool screenshots.
- Optional internal performance diagnostics and Windhawk/DbgView logging.
- No permanent clock or date element.

## How It Works

After the configured inactivity timeout, BubbleGlass creates a transparent topmost layered window above the desktop. Transparent bubbles are rendered into a 32-bit premultiplied-alpha back buffer and composited with `UpdateLayeredWindow()`.

The animation uses QPC-based frame pacing and a high-resolution waitable timer where available. Normal keyboard or mouse activity dismisses BubbleGlass and returns immediately to the desktop.

## Rendering

BubbleGlass uses:

- GDI+ vector rendering.
- 32-bit premultiplied-alpha DIB back buffer.
- `UpdateLayeredWindow()` for per-pixel desktop composition.
- QPC-based 60 FPS frame pacing.
- High-resolution waitable timer where available.
- Direct premultiplied DIB clearing.
- Reusable GDI+ pens and brushes.

The bubbles are rendered primarily as transparent outlines, highlights, reflections and thin-film interference arcs rather than opaque filled circles.

## Bubble Appearance

Each bubble can contain iridescent rainbow arcs, a transparent membrane rim, curved specular highlights, a small highlight hotspot, faint opposite-side reflection, organic deformation, slowly changing interference colors, optional subtle shadow and an animated expanding pop ring.

## Motion and Physics

Motion includes individual velocity, size-dependent behavior, gentle organic side movement, optional turbulence, bubble-to-bubble collisions, edge bouncing and optional screen-edge wrapping.

Bubble collisions use a lightly damped equal-mass impulse model. Larger and smaller bubbles can also receive different effective lifetimes.

## Multi-Monitor Support

When **Span all monitors** is enabled, BubbleGlass uses the complete Windows virtual desktop area so bubbles can move across a multi-monitor setup as one continuous surface.

When disabled, BubbleGlass uses only the primary monitor.

## Settings

| Setting | Default | Description |
|---|---:|---|
| Inactivity timeout | 30 s | Time without input before BubbleGlass appears |
| Target bubble count | 42 | Maximum simultaneous bubbles |
| Span all monitors | Off | Use the complete Windows virtual desktop |
| Mouse dismiss threshold | 6 px | Filters tiny mouse-sensor movements |
| Minimum bubble diameter | 60 px | Minimum size when variation is enabled |
| Maximum bubble diameter | 620 px | Maximum bubble size |
| Vary bubble sizes | On | Mixes many small/medium bubbles with fewer large bubbles |
| Motion speed | 100% | 100% = normal speed |
| Spawn interval | 650 ms | Delay between new bubbles |
| Turbulence | 15 | 0 = pure billiard-style movement |
| Bubble collisions | On | Enables bubble-to-bubble collisions |
| Bounce off screen edges | On | Off = wrap to opposite edge |
| Minimum lifetime | 60 s | Minimum approximate lifetime |
| Maximum lifetime | 240 s | Maximum approximate lifetime |
| Pop animation | On | Animate bubbles when lifetime ends |
| Pop duration | 220 ms | Duration of the burst animation |
| Maximum pop size | 122% | Expansion before disappearing |
| Bubble opacity | 80% | Overall bubble visibility |
| Thin-film iridescence | On | Animated rainbow interference colors |
| Iridescent color-cycle speed | 100% | 0% freezes the interference colors |
| Subtle bubble shadows | Off | Faint lower-right reflection/shadow arc |
| Desktop dimming | 8% | 0% disables dimming |
| Internal performance stats | Off | On-screen diagnostics |
| Windhawk/DbgView performance log | Off | One performance line per second |

## Performance Diagnostics

The optional diagnostics overlay can show FPS, frame time, jitter, rendering work time, waiting time, physics time, bubble drawing time, clear time, surface setup time, present time and active bubble count.

Example logging output:

    FPS=60.0
    frame=16.67ms
    work=15.7ms
    wait=1.0ms
    physics=0.01ms
    clear=2.6ms
    draw=9.7ms
    present=3.3ms
    jitter=0.7ms
    bubbles=42

Diagnostics and logging are disabled by default.

## Performance

Version **1.7.4** targets **60 FPS** and was tested with:

- 42 simultaneous bubbles.
- A 7680 × 2160 desktop surface.
- Multi-monitor / ultra-wide desktop rendering.
- Live Windows desktop composition.

Actual performance depends on resolution, bubble count, bubble sizes, Windows composition load and hardware.

If performance is insufficient, reducing bubble count, maximum bubble size, iridescence or total desktop resolution has the largest effect.

## Installation

1. Install [Windhawk](https://windhawk.net/).
2. Open Windhawk.
3. Install or import the `bubble-glass-saver` mod source.
4. Enable the mod.
5. Configure the settings you want.

BubbleGlass runs inside `explorer.exe`. No separate `.scr` screensaver file is required.

## Usage

1. Enable BubbleGlass.
2. Configure the inactivity timeout.
3. Leave the computer idle.
4. BubbleGlass appears automatically.
5. Move the mouse or press a normal key to dismiss it.

For screenshots, press **Print Screen**. BubbleGlass temporarily ignores dismissal input so Windows Snipping Tool can be used.

## Compatibility

- Windows 11.
- Windhawk.
- Runs inside `explorer.exe`.
- Uses standard Windows GDI/GDI+ and layered-window APIs.
- Does not require DirectX, CUDA or a dedicated GPU API.

## Release

Current version: **1.7.4**

See [Releases](https://github.com/SilverAmd/BubbleGlass-Screensaver/releases) for release downloads and the full-quality video demo.

## Credits

Developed and tested by **SilverAmd** with iterative performance analysis, profiling and optimization.

Special focus was placed on smooth frame pacing, large desktop resolutions, multi-monitor support, low rendering overhead and maintaining transparency of the live Windows desktop.

## License

Licensed under the MIT License. See [LICENSE](LICENSE).
