// ==WindhawkMod==
// @id              bubble-glass-saver
// @name            BubbleGlass Screensaver
// @description     Transparent soap-bubble screensaver after inactivity. GDI+ per-pixel alpha: desktop stays live beneath. Instant dismiss on mouse move or keystroke.
// @version         1.7.5
// @author          SilverAmd
// @github          https://github.com/SilverAmd
// @include         windhawk.exe
// @compilerOptions -lgdiplus -lgdi32 -lwinmm -lshell32 -lwtsapi32 -luser32
// ==/WindhawkMod==

// ==WindhawkModSettings==
/*
- idleTimeoutSec: 30
  $name: General - Inactivity timeout (seconds)
  $description: Seconds of no input before BubbleGlass appears.

- bubbleCount: 42
  $name: General - Target bubble count
  $description: Maximum number of bubbles on screen. New bubbles arrive gradually.

- multiMonitor: false
  $name: General - Span all monitors

- dismissDeltaPx: 6
  $name: General - Mouse dismiss threshold (px)
  $description: Mouse travel beyond this distance closes BubbleGlass.

- minBubbleSize: 60
  $name: Bubble Size - Minimum diameter (px)
  $description: Used when Size variation is enabled.

- maxBubbleSize: 620
  $name: Bubble Size - Maximum diameter (px)

- sizeVariation: true
  $name: Bubble Size - Vary bubble sizes
  $description: On = many small/medium and fewer very large bubbles. Off = all bubbles use Max diameter.

- driftSpeedPercent: 100
  $name: Motion - Speed (%)
  $description: 100 = normal speed, 200 = double speed.

- spawnIntervalMs: 650
  $name: Motion - Spawn interval (ms)
  $description: Delay between new bubbles while filling or replacing popped bubbles.

- turbulence: 15
  $name: Motion - Turbulence / air current (0-100)
  $description: 0 = pure billiard motion. Higher values add a gentle changing air current.

- bubbleCollisions: true
  $name: Physics - Bubble-to-bubble collisions

- wallCollisions: true
  $name: Physics - Bounce off screen edges
  $description: Off = bubbles wrap to the opposite edge instead of bouncing.

- minLifetimeSec: 60
  $name: Lifetime - Minimum lifetime (seconds)

- maxLifetimeSec: 240
  $name: Lifetime - Maximum lifetime (seconds)
  $description: Larger bubbles tend to live longer inside this range.

- popEnabled: true
  $name: Pop - Animate bubbles when lifetime ends

- popDurationMs: 220
  $name: Pop - Animation duration (ms)

- popGrowthPercent: 122
  $name: Pop - Maximum size while popping (%)
  $description: 122 = bubble expands to about 122 percent before disappearing.

- bubbleOpacity: 80
  $name: Appearance - Bubble opacity (%)

- iridescence: true
  $name: Appearance - Thin-film iridescence

- iridescenceArcCount: 4
  $name: Performance - Rainbow arcs per bubble (2-4)
  $description: >-
    4 = original full-color detail (unchanged appearance).
    3 = balanced, 2 = faster with fewer reflections. Compare FPS and appearance
    using the same bubble count. Only applies when iridescence is enabled.

- colorCycleSpeedPercent: 100
  $name: Appearance - Iridescent color cycle speed (%)
  $description: 0 freezes the interference colors. 100 = normal.

- showShadows: false
  $name: Appearance - Subtle bubble shadows

- dimPercent: 8
  $name: Appearance - Desktop dim (%)
  $description: 0 = no dimming. The live desktop/video remains visible underneath.

- showPerformanceStats: false
  $name: Diagnostics - Show internal performance stats
  $description: >-
    Shows BubbleGlass' own measured FPS, frame interval, render/present time,
    jitter and bubble count. Useful for performance diagnostics and frame-time analysis.

- logPerformanceStats: false
  $name: Diagnostics - Log performance stats to Windhawk/DbgView
  $description: Writes one performance line per second while the saver is active.

- profileBubbleDraw: false
  $name: Diagnostics - Profile detailed bubble drawing time
  $description: With performance logging enabled, log timing for rainbow arcs, rim, highlights and reflections. Disabled by default to avoid profiling overhead.
*/
// ==/WindhawkModSettings==

// ==WindhawkModReadme==
/*
# BubbleGlass Screensaver

A transparent, animated soap-bubble screensaver for the Windows desktop.

BubbleGlass displays colorful, iridescent soap bubbles directly above the live
Windows desktop after a configurable period of inactivity. The desktop remains
visible underneath because the saver uses a transparent layered window with
per-pixel alpha blending.

The animation is designed for smooth 60 FPS rendering while remaining lightweight
enough to run across large and multi-monitor desktops.

## Preview

![BubbleGlass Screensaver preview](https://i.imgur.com/Nh5EyFe.png)

![BubbleGlass Screensaver animated preview](https://i.imgur.com/gCsmdj6.gif)

*Transparent, animated soap bubbles move across the live Windows desktop while
the desktop remains visible underneath. The optional diagnostics overlay shows
real-time FPS, frame time, jitter and rendering performance.*

## Features

- Transparent screensaver displayed directly above the live Windows desktop.
- Smooth 60 FPS animation target.
- Per-pixel transparency using a layered Windows window.
- Colorful thin-film iridescent bubble rendering.
- Animated rainbow interference colors.
- Multiple bubble sizes.
- Gradual bubble spawning instead of filling the screen instantly.
- Natural drifting motion.
- Optional air-current / turbulence simulation.
- Bubble-to-bubble collision physics.
- Optional wall bouncing or screen-edge wrapping.
- Configurable bubble lifetime.
- Animated bubble popping.
- Adjustable pop growth effect.
- Configurable overall bubble opacity.
- Optional subtle bubble shadows.
- Optional desktop dimming.
- Multi-monitor support.
- Configurable mouse movement threshold for dismissing the screensaver.
- Any normal keyboard input immediately dismisses the screensaver.
- Mouse movement, mouse buttons and mouse wheel dismiss the screensaver.
- Desktop remains interactive again immediately after dismissal.
- Optional internal performance diagnostics.
- Optional Windhawk performance logging.
- Designed to avoid permanent static clock/date elements on the screen.

## How It Works

BubbleGlass monitors Windows input activity.

After the configured inactivity timeout is reached, a transparent topmost window
is created over the desktop. The window does not replace the desktop image and
does not capture normal desktop contents.

Instead, transparent soap bubbles are rendered into a 32-bit per-pixel-alpha
back buffer and composited over the existing Windows desktop.

The animation runs on its own rendering loop using high-resolution frame timing.

As soon as keyboard or mouse activity is detected, BubbleGlass closes immediately
and the normal desktop remains exactly as it was.

## Rendering

BubbleGlass uses:

- GDI+ vector rendering.
- 32-bit premultiplied-alpha DIB back buffer.
- `UpdateLayeredWindow()` for per-pixel desktop composition.
- QPC-based frame pacing.
- High-resolution waitable timer where available.
- Direct premultiplied DIB clearing.
- Reusable GDI+ pens and brushes for bubble rendering.

The bubbles are rendered primarily as transparent outlines, highlights,
reflections and thin-film interference arcs rather than opaque filled circles.

This allows the Windows wallpaper, icons, applications and other desktop content
to remain visible through the bubbles.

## Bubble Appearance

Each bubble can contain:

- Iridescent rainbow arcs.
- Transparent membrane rim.
- Curved specular highlight.
- Small highlight hotspot.
- Faint opposite-side reflection.
- Organic shape deformation.
- Slowly changing interference colors.
- Optional subtle shadow.
- Animated expanding pop ring.

Bubble appearance changes continuously over time so that the animation does not
remain visually static.

## Motion and Physics

Bubbles gradually enter the desktop and move independently.

Motion includes:

- Individual velocity.
- Size-dependent behavior.
- Gentle organic side movement.
- Optional turbulence / air-current simulation.
- Bubble-to-bubble collisions.
- Edge bouncing.
- Optional screen-edge wrapping.

Bubble collisions use a lightly damped equal-mass impulse model.

Large, medium and small bubbles can also receive different effective lifetimes,
helping the overall scene change continuously.

## Pop Animation

When a bubble reaches the end of its lifetime it can perform a short pop animation.

The effect includes:

- Bubble expansion.
- Membrane fade-out.
- Temporary brightness increase.
- Expanding white pop ring.

After the animation finishes, the bubble disappears and a replacement bubble can
be spawned later.

## Multi-Monitor Support

When **Span all monitors** is enabled, BubbleGlass uses the complete Windows
virtual desktop area.

This allows bubbles to move across multi-monitor configurations as one continuous
desktop surface.

When disabled, BubbleGlass uses only the primary monitor.

## Settings

### General

**Inactivity timeout**

Time in seconds without keyboard or mouse input before BubbleGlass appears.

Default:

`30 seconds`

---

**Target bubble count**

Maximum number of simultaneously active bubbles.

Bubbles are added gradually until the configured number is reached.

Default:

`42`

---

**Span all monitors**

When enabled, BubbleGlass covers the complete Windows virtual desktop.

Default:

`Off`

---

**Mouse dismiss threshold**

Minimum mouse movement required before BubbleGlass closes.

This prevents tiny mouse sensor movements from immediately dismissing the saver.

Default:

`6 px`

## Bubble Size

**Minimum bubble diameter**

Minimum bubble size when size variation is enabled.

Default:

`60 px`

---

**Maximum bubble diameter**

Maximum bubble size.

Default:

`620 px`

---

**Vary bubble sizes**

Creates many small and medium bubbles together with fewer very large bubbles.

When disabled, bubbles use the configured maximum size.

Default:

`On`

## Motion

**Speed**

Controls overall bubble movement speed.

`100%` = normal speed.

Default:

`100%`

---

**Spawn interval**

Delay between newly created bubbles while the desktop is filling or while
expired bubbles are being replaced.

Default:

`650 ms`

---

**Turbulence / air current**

Adds gently changing air movement to bubble trajectories.

`0` = pure billiard-style movement.

Higher values create stronger directional variation.

Default:

`15`

## Physics

**Bubble-to-bubble collisions**

Allows bubbles to collide and exchange momentum.

Default:

`On`

---

**Bounce off screen edges**

When enabled, bubbles bounce from the desktop edges.

When disabled, bubbles wrap to the opposite side.

Default:

`On`

## Lifetime

**Minimum lifetime**

Minimum approximate lifetime of a bubble.

Default:

`60 seconds`

---

**Maximum lifetime**

Maximum approximate lifetime.

Larger bubbles tend to receive longer lifetimes within the configured range.

Default:

`240 seconds`

## Pop Effect

**Animate bubbles when lifetime ends**

Enables the bubble burst animation.

Default:

`On`

---

**Pop animation duration**

Duration of the burst animation.

Default:

`220 ms`

---

**Maximum pop size**

Controls how much the bubble expands while popping.

Default:

`122%`

## Appearance

**Bubble opacity**

Controls the overall visibility of the bubbles.

Default:

`80%`

---

**Thin-film iridescence**

Enables animated rainbow interference colors around the bubble membrane.

Default:

`On`

---

**Iridescent color cycle speed**

Controls how quickly the thin-film colors move around the bubbles.

`0%` freezes the interference colors.

Default:

`100%`

---

**Subtle bubble shadows**

Adds a faint lower-right shadow/reflection arc.

Default:

`Off`

---

**Desktop dimming**

Adds a subtle translucent dark layer behind the bubbles while keeping the live
desktop visible.

`0%` disables dimming.

Default:

`8%`

## Performance Diagnostics

BubbleGlass includes its own optional internal performance monitor.

Enable **Show internal performance stats** to display information such as:

- FPS.
- Frame time.
- Frame-time jitter.
- Rendering work time.
- Waiting time.
- Physics time.
- Bubble drawing time.
- Clear time.
- Surface setup time.
- Present time.
- Active bubble count.

This is useful for testing performance on different resolutions and hardware.

The diagnostics overlay is disabled by default.

## Performance Logging

Enable **Log performance stats to Windhawk/DbgView** to write approximately one
performance report per second.

Example values include:

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

Logging is intended mainly for diagnostics and development and is disabled by
default.

## Performance

BubbleGlass was designed and optimized using real frame-time measurements instead
of relying only on theoretical rendering optimizations.

The renderer targets:

**60 FPS**

The final version has been tested with:

- 42 simultaneous bubbles.
- A 7680 × 2160 desktop surface.
- Multi-monitor / ultra-wide desktop rendering.
- Live Windows desktop composition.

Actual performance depends on screen resolution, configured bubble count, bubble
sizes, Windows composition load and hardware.

If performance is insufficient, reducing the following settings will have the
largest effect:

1. Bubble count.
2. Maximum bubble size.
3. Iridescence.
4. Screen resolution / total virtual desktop area.

## Usage

1. Install and enable the BubbleGlass Screensaver mod.
2. Configure the inactivity timeout.
3. Leave the computer idle.
4. BubbleGlass appears automatically.
5. Move the mouse or press a key to dismiss it.

No separate `.scr` screensaver file is required.

## Notes

BubbleGlass intentionally keeps the underlying Windows desktop visible.

It is therefore different from traditional screensavers which replace the entire
screen with a separate full-screen scene.

The mod also intentionally does not display a permanent clock or date. Static
elements would remain at the same screen position and would conflict with the
goal of keeping the display visually dynamic.

## Compatibility

Designed for Windows 11 and Windhawk.

The mod runs inside:

`explorer.exe`

Rendering uses standard Windows GDI/GDI+ and layered-window APIs and does not
require DirectX, CUDA or a dedicated GPU API.

## Credits

Developed and tested by **SilverAmd** with iterative performance analysis,
profiling and optimization.

Special focus was placed on:

- Smooth frame pacing.
- Large desktop resolutions.
- Multi-monitor support.
- Low rendering overhead.
- Maintaining transparency of the live Windows desktop.
*/
// ==/WindhawkModReadme==


// v1.7.5 RC4: QPC-based physics time step and precision-safe animation clocks.
//   * exact QPC-based 60 FPS frame pacing
//   * high-resolution waitable timer
//   * fast direct premultiplied DIB clear
//   * persistent GDI+ bubble pens/brushes
//   * optimized transparent vector bubble rendering
//   * optional lightweight FPS/frame-time diagnostics
//   * multi-monitor support and instant input dismissal

#include <windows.h>
#include <shellapi.h>
#include <wtsapi32.h>
#include <cstring>
#include <gdiplus.h>
#include <vector>
#include <random>
#include <cmath>
#include <string>
#include <cwchar>
#include <mmsystem.h>
#include <algorithm>
#include <memory>

#ifndef CREATE_WAITABLE_TIMER_HIGH_RESOLUTION
#define CREATE_WAITABLE_TIMER_HIGH_RESOLUTION 0x00000002
#endif

using namespace Gdiplus;

constexpr DWORD FADE_IN_MS = 400;
constexpr float COLLISION_RESTITUTION = 0.985f;
constexpr UINT WM_BUBBLE_SETTINGS_CHANGED = WM_APP + 101;
constexpr UINT WM_BUBBLE_DISMISS = WM_APP + 102;
constexpr UINT WM_BUBBLE_INPUT_ARM = WM_APP + 103;
constexpr UINT WM_BUBBLE_INPUT_DISARM = WM_APP + 104;

struct Settings {
	// General
	int  idleTimeoutSec    = 30;
	int  bubbleCount       = 42;
	BOOL multiMonitor      = TRUE;
	int  dismissDeltaPx    = 6;

	// Bubble size
	int  minBubbleSize     = 60;
	int  maxBubbleSize     = 620;
	BOOL sizeVariation     = TRUE;

	// Motion / physics
	int  driftSpeedPercent = 100;
	int  spawnIntervalMs   = 650;
	int  turbulence        = 15;     // 0..100
	BOOL bubbleCollisions  = TRUE;
	BOOL wallCollisions    = TRUE;

	// Lifetime / pop
	int  minLifetimeSec    = 60;
	int  maxLifetimeSec    = 240;
	BOOL popEnabled        = TRUE;
	int  popDurationMs     = 220;
	int  popGrowthPercent  = 122;

	// Appearance
	int  bubbleOpacity          = 80;
	BOOL iridescence            = TRUE;
    int  iridescenceArcCount   = 4;
	int  colorCycleSpeedPercent = 100;
	BOOL showShadows            = FALSE;
	int  dimPercent             = 8;

	// Diagnostics
	BOOL showPerformanceStats   = FALSE;
	BOOL logPerformanceStats    = FALSE;
    BOOL profileBubbleDraw      = FALSE;

	float Drift() const {
		return driftSpeedPercent / 100.0f;
	}

	float ColorCycle() const {
		return colorCycleSpeedPercent / 100.0f;
	}

	float PopDurationSec() const {
		return popDurationMs / 1000.0f;
	}

	float PopGrowth() const {
		return (popGrowthPercent - 100) / 100.0f;
	}
} g_settings;

struct Bubble {
	float x, y, r;
	float vy, vx;
	float wobAmp, wobFreq, phase, hue, alpha;

	// Hybrid extension: long life followed by a short visible pop animation.
	float life;
	bool  popping;
	float popProgress;
};

// ---- globals ----
// These hook variables and callbacks are used only on the input thread.
static HHOOK g_mouseHook = nullptr;
static HHOOK g_kbdHook = nullptr;
static HANDLE g_inputThread = nullptr;
static DWORD g_inputThreadId = 0;
static HANDLE g_inputReadyEvent = nullptr;
static HWND g_inputWindow = nullptr;
static bool g_hookArmed = false;
static bool g_hookDismissPosted = false;
static POINT g_hookAtShow{};
static int g_hookThreshold = 6;
static UINT_PTR g_hookSerial = 0;
static ULONGLONG g_hookGraceUntil = 0;

// Only the UI thread reads/writes the current display generation.
static UINT_PTR g_showSerial = 0;
static HWND  g_saverWnd  = nullptr;
// The notification window and its state are owned by BubbleUiThread.
static HWND g_controlWnd = nullptr;
static bool g_controlClassRegistered = false;
static bool g_sessionNotificationsRegistered = false;
static HPOWERNOTIFY g_displayPowerNotification = nullptr;
static bool g_sessionLocked = false;
static bool g_sessionDisconnected = false;
static bool g_displayOff = false;
static ULONGLONG g_resumeGraceUntil = 0;

constexpr GUID kConsoleDisplayState = {
    0x6fe69556, 0x704a, 0x47a0,
    {0x8f, 0x24, 0xc2, 0x8d, 0x93, 0x6f, 0xda, 0x47}
};

bool IsDesktopUnavailable() {
    return g_sessionLocked || g_sessionDisconnected || g_displayOff;
}
static bool  g_saverOn   = false;
static bool  g_rendering = false;
static bool  g_classRegistered = false;
static std::vector<Bubble> g_bubbles;
static std::mt19937 g_rng;
static ULONG_PTR g_gdiplusToken = 0;
static UINT_PTR  g_idleTimer    = 0;
static int   g_vx = 0, g_vy = 0, g_vw = 0, g_vh = 0;
static ULONGLONG g_showTick = 0;
static float g_fade = 0.0f;
static HDC     g_memDC  = nullptr;
static HBITMAP g_hBmp   = nullptr;
static HBITMAP g_oldBmp = nullptr;
static void* g_bitmapBits = nullptr;
static HANDLE g_uiThread = nullptr;
static DWORD  g_uiThreadId = 0;
static HANDLE g_uiReadyEvent = nullptr;
// QPC-based simulation timing, separate from the frame pacer.
static LONGLONG g_lastFrameQpc = 0;
static LONGLONG g_showQpc = 0;
static ULONGLONG g_lastBubbleSpawnTick = 0;

// exact 60 FPS pacing.
static LARGE_INTEGER g_qpcFrequency{};
static LONGLONG g_nextFrameQpc = 0;
static LONGLONG g_frameIntervalQpc = 0;

static HANDLE g_frameTimer = nullptr;
static bool g_timerPeriodActive = false;

// ---- lightweight performance diagnostics ----
struct BubbleDrawDetails {
    double setupMs = 0.0;
    double rainbowMs = 0.0;
    double rimMs = 0.0;
    double highlightMs = 0.0;
    double shineMs = 0.0;
    double lowerMs = 0.0;
    double popMs = 0.0;
};

struct PerfBreakdown {
    BubbleDrawDetails detail{};
	double physicsMs    = 0.0;
	double surfaceMs    = 0.0;
	double clearMs      = 0.0;
	double bubbleDrawMs = 0.0;
	double hudMs        = 0.0;
	double gfxFinishMs  = 0.0;
	double presentMs    = 0.0;
};

struct PerformanceStats {
	LARGE_INTEGER frequency{};
	LARGE_INTEGER renderStart{};
	LARGE_INTEGER lastPresent{};

	double frameMs[120] {};
	double renderMs[120] {};
	PerfBreakdown breakdown[120] {};

	int sampleCount = 0;
	int sampleIndex = 0;

	PerfBreakdown current{};
	PerfBreakdown avg{};

	ULONGLONG lastSummaryTick = 0;
	ULONGLONG lastLogTick = 0;

	double fps = 0.0;
	double avgFrameMs = 0.0;
	double avgRenderMs = 0.0;
	double avgWaitMs = 0.0;

	double jitterMs = 0.0;
	double maxFrameMs = 0.0;
	double maxRenderMs = 0.0;

	std::wstring textLine1;
	std::wstring textLine2;
	std::wstring textLine3;
	std::wstring textLine4;
} g_perf;

struct BubbleGdiResources {
	Pen shadowPen;
	Pen irisPen;
	Pen rimPen;
	Pen highlightPen;
	SolidBrush shineBrush;
	Pen lowerReflectionPen;
	Pen flashPen;

	BubbleGdiResources()
		: shadowPen(Color(0, 0, 0, 0), 1.0f),
		  irisPen(Color(0, 0, 0, 0), 1.0f),
		  rimPen(Color(0, 0, 0, 0), 1.0f),
		  highlightPen(Color(0, 0, 0, 0), 1.0f),
		  shineBrush(Color(0, 0, 0, 0)),
		  lowerReflectionPen(Color(0, 0, 0, 0), 1.0f),
		  flashPen(Color(0, 0, 0, 0), 1.0f) {

		shadowPen.SetLineCap(
		    LineCapRound, LineCapRound, DashCapRound);

		irisPen.SetLineCap(
		    LineCapRound, LineCapRound, DashCapRound);

		highlightPen.SetLineCap(
		    LineCapRound, LineCapRound, DashCapRound);

		lowerReflectionPen.SetLineCap(
		    LineCapRound, LineCapRound, DashCapRound);
	}
};

static std::unique_ptr<BubbleGdiResources> g_bubbleGdi;

// ---- forward declarations ----
void  LoadSettings();
void  RegisterSaverClass();
void  UnregisterSaverClass();
void  CreateBackBuffer(int w, int h);
void  DestroyBackBuffer();
void  SeedBubbles(int width, int height);
Bubble SpawnBubble(bool anywhere, int W, int H);
void  StartRenderLoop();
void  StopRenderLoop();
void  RenderFrame();
void  DrawBubble(Graphics& gfx, const Bubble& b, float fadeAlpha,
                 double animationSeconds);
void  ResetPerformanceStats();
void  BeginPerformanceFrame();
void  EndPerformanceFrame();
void  DrawPerformanceStats(Graphics& gfx, float fadeAlpha);

Color HslToColor(float h, float s, float l, BYTE a);
void  ShowSaver();
void  HideSaver(const char* reason);
bool  IsIdle(DWORD* outIdleMs);
LRESULT CALLBACK SaverWndProc(HWND hWnd, UINT uMsg,
                              WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KbdProc(int nCode, WPARAM wParam, LPARAM lParam);
VOID CALLBACK IdleTimer(HWND, UINT, UINT_PTR, DWORD);
DWORD WINAPI BubbleUiThread(LPVOID);

// ================= settings =================
int ClampSetting(int value, int minimum, int maximum) {
	if (value < minimum) return minimum;
	if (value > maximum) return maximum;
	return value;
}

// Windhawk provides no automatic loader: every mod defines its
// own LoadSettings() and reads values via Wh_GetIntSetting().
void LoadSettings() {
	// General
	g_settings.idleTimeoutSec =
	    ClampSetting(Wh_GetIntSetting(L"idleTimeoutSec", 30), 1, 1800);

	g_settings.bubbleCount =
	    ClampSetting(Wh_GetIntSetting(L"bubbleCount", 42), 0, 120);

	g_settings.multiMonitor =
	    Wh_GetIntSetting(L"multiMonitor", 1) ? TRUE : FALSE;

	g_settings.dismissDeltaPx =
	    ClampSetting(Wh_GetIntSetting(L"dismissDeltaPx", 6), 1, 50);

	// Bubble size
	g_settings.minBubbleSize =
	    ClampSetting(Wh_GetIntSetting(L"minBubbleSize", 60), 20, 1600);

	g_settings.maxBubbleSize =
	    ClampSetting(Wh_GetIntSetting(L"maxBubbleSize", 620), 20, 1600);

	if (g_settings.minBubbleSize > g_settings.maxBubbleSize) {
		int tmp = g_settings.minBubbleSize;
		g_settings.minBubbleSize = g_settings.maxBubbleSize;
		g_settings.maxBubbleSize = tmp;
	}

	g_settings.sizeVariation =
	    Wh_GetIntSetting(L"sizeVariation", 1) ? TRUE : FALSE;

	// Motion / physics
	g_settings.driftSpeedPercent =
	    ClampSetting(Wh_GetIntSetting(L"driftSpeedPercent", 100), 10, 500);

	g_settings.spawnIntervalMs =
	    ClampSetting(Wh_GetIntSetting(L"spawnIntervalMs", 650), 100, 10000);

	g_settings.turbulence =
	    ClampSetting(Wh_GetIntSetting(L"turbulence", 15), 0, 100);

	g_settings.bubbleCollisions =
	    Wh_GetIntSetting(L"bubbleCollisions", 1) ? TRUE : FALSE;

	g_settings.wallCollisions =
	    Wh_GetIntSetting(L"wallCollisions", 1) ? TRUE : FALSE;

	// Lifetime / pop
	g_settings.minLifetimeSec =
	    ClampSetting(Wh_GetIntSetting(L"minLifetimeSec", 60), 5, 7200);

	g_settings.maxLifetimeSec =
	    ClampSetting(Wh_GetIntSetting(L"maxLifetimeSec", 240), 5, 7200);

	if (g_settings.minLifetimeSec > g_settings.maxLifetimeSec) {
		int tmp = g_settings.minLifetimeSec;
		g_settings.minLifetimeSec = g_settings.maxLifetimeSec;
		g_settings.maxLifetimeSec = tmp;
	}

	g_settings.popEnabled =
	    Wh_GetIntSetting(L"popEnabled", 1) ? TRUE : FALSE;

	g_settings.popDurationMs =
	    ClampSetting(Wh_GetIntSetting(L"popDurationMs", 220), 50, 2000);

	g_settings.popGrowthPercent =
	    ClampSetting(Wh_GetIntSetting(L"popGrowthPercent", 122), 100, 200);

	// Appearance
	g_settings.bubbleOpacity =
	    ClampSetting(Wh_GetIntSetting(L"bubbleOpacity", 80), 5, 100);

	g_settings.iridescence =
	    Wh_GetIntSetting(L"iridescence", 1) ? TRUE : FALSE;

    // GDI+ anti-aliased DrawArc calls dominate work with 42 bubbles.
    // Quality selection changes only the number of rainbow arcs, never
    // the frame rate target, transparency, or bubble physics.
    g_settings.iridescenceArcCount =
        ClampSetting(Wh_GetIntSetting(L"iridescenceArcCount", 4), 2, 4);

	g_settings.colorCycleSpeedPercent =
	    ClampSetting(Wh_GetIntSetting(L"colorCycleSpeedPercent", 100), 0, 500);

	g_settings.showShadows =
	    Wh_GetIntSetting(L"showShadows", 0) ? TRUE : FALSE;

	g_settings.dimPercent =
	    ClampSetting(Wh_GetIntSetting(L"dimPercent", 8), 0, 60);

	// Diagnostics
	g_settings.showPerformanceStats =
	    Wh_GetIntSetting(L"showPerformanceStats", 0) ? TRUE : FALSE;

	g_settings.logPerformanceStats =
	    Wh_GetIntSetting(L"logPerformanceStats", 0) ? TRUE : FALSE;

    g_settings.profileBubbleDraw =
        Wh_GetIntSetting(L"profileBubbleDraw", 0) ? TRUE : FALSE;
}

// ================= input hooks =================
// This dedicated thread pumps low-level keyboard/mouse hooks without ever
// rendering frames. Hooks exist only while the saver is visible. The callbacks
// never block Windows input or call the UI thread synchronously.
void QueueDismiss(int reason) {
    if (!g_hookArmed || g_hookDismissPosted || !g_uiThreadId)
        return;
    if (PostThreadMessageW(g_uiThreadId, WM_BUBBLE_DISMISS,
                           static_cast<WPARAM>(g_hookSerial),
                           static_cast<LPARAM>(reason))) {
        g_hookDismissPosted = true;
    }
}

LRESULT CALLBACK KbdProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && g_hookArmed &&
        (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        const auto* kb = reinterpret_cast<const KBDLLHOOKSTRUCT*>(lParam);
        if (kb && kb->vkCode == VK_SNAPSHOT) {
            // Preserve the ability to take a Snipping Tool screenshot.
            g_hookGraceUntil = GetTickCount64() + 5000;
        } else if (GetTickCount64() >= g_hookGraceUntil) {
            QueueDismiss(1);  // Key press.
        }
    }
    return CallNextHookEx(g_kbdHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && g_hookArmed &&
        GetTickCount64() >= g_hookGraceUntil) {
        const auto* ms = reinterpret_cast<const MSLLHOOKSTRUCT*>(lParam);
        if (ms) {
            if (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN ||
                wParam == WM_MBUTTONDOWN || wParam == WM_XBUTTONDOWN ||
                wParam == WM_MOUSEWHEEL || wParam == WM_MOUSEHWHEEL) {
                QueueDismiss(2);  // Click or wheel.
            } else if (wParam == WM_MOUSEMOVE) {
                LONGLONG dx = static_cast<LONGLONG>(ms->pt.x) -
                              g_hookAtShow.x;
                LONGLONG dy = static_cast<LONGLONG>(ms->pt.y) -
                              g_hookAtShow.y;
                LONGLONG threshold = g_hookThreshold;
                if (dx * dx + dy * dy >= threshold * threshold)
                    QueueDismiss(3);  // Mouse movement.
            }
        }
    }
    return CallNextHookEx(g_mouseHook, nCode, wParam, lParam);
}

void DisarmInputHooks() {
    const bool wasArmed = g_hookArmed;
    g_hookArmed = false;
    if (g_mouseHook) {
        UnhookWindowsHookEx(g_mouseHook);
        g_mouseHook = nullptr;
    }
    if (g_kbdHook) {
        UnhookWindowsHookEx(g_kbdHook);
        g_kbdHook = nullptr;
    }
    g_hookDismissPosted = false;
    if (wasArmed)
        Wh_Log(L"BubbleGlass input hooks disarmed");
}

LRESULT CALLBACK InputWndProc(HWND hWnd, UINT message,
                              WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_BUBBLE_INPUT_ARM: {
            DisarmInputHooks();
            g_hookThreshold = static_cast<int>(wParam);
            g_hookSerial = static_cast<UINT_PTR>(lParam);
            g_hookGraceUntil = 0;
            if (!GetCursorPos(&g_hookAtShow)) {
                Wh_Log(L"BubbleGlass: GetCursorPos(input) failed");
                return FALSE;
            }

            g_mouseHook = SetWindowsHookExW(WH_MOUSE_LL, MouseProc,
                                            nullptr, 0);
            if (!g_mouseHook) {
                Wh_Log(L"BubbleGlass: mouse hook failed (%lu)",
                       GetLastError());
                DisarmInputHooks();
                return FALSE;
            }
            g_kbdHook = SetWindowsHookExW(WH_KEYBOARD_LL, KbdProc,
                                          nullptr, 0);
            if (!g_kbdHook) {
                Wh_Log(L"BubbleGlass: keyboard hook failed (%lu)",
                       GetLastError());
                DisarmInputHooks();
                return FALSE;
            }
            g_hookArmed = true;
            Wh_Log(L"BubbleGlass input hooks armed");
            return TRUE;
        }
        case WM_BUBBLE_INPUT_DISARM:
            DisarmInputHooks();
            return TRUE;
        case WM_CLOSE:
            DisarmInputHooks();
            DestroyWindow(hWnd);
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hWnd, message, wParam, lParam);
}

DWORD WINAPI BubbleInputThread(LPVOID) {
    HINSTANCE instance = GetModuleHandleW(nullptr);
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.hInstance = instance;
    wc.lpfnWndProc = InputWndProc;
    wc.lpszClassName = L"BubbleGlassInputControl";
    bool registered = RegisterClassExW(&wc) != 0;
    if (!registered) {
        Wh_Log(L"BubbleGlass: input window class registration failed (%lu)",
               GetLastError());
    }

    HWND wnd = registered ? CreateWindowExW(
        0, L"BubbleGlassInputControl", L"", 0,
        0, 0, 0, 0, HWND_MESSAGE, nullptr, instance, nullptr) : nullptr;
    if (registered && !wnd) {
        Wh_Log(L"BubbleGlass: input window creation failed (%lu)",
               GetLastError());
    }
    g_inputWindow = wnd;
    if (g_inputReadyEvent)
        SetEvent(g_inputReadyEvent);

    if (wnd) {
        Wh_Log(L"BubbleGlass input thread ready");
        MSG message{};
        while (GetMessageW(&message, nullptr, 0, 0) > 0) {
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
        DisarmInputHooks();
        if (IsWindow(wnd))
            DestroyWindow(wnd);
    }

    g_inputWindow = nullptr;
    if (registered)
        UnregisterClassW(L"BubbleGlassInputControl", instance);
    return wnd ? 0 : 1;
}

// ================= idle watchdog =================

// Runs on a 250 ms timer. Near-zero cost while dismissed.
VOID CALLBACK IdleTimer(HWND, UINT, UINT_PTR, DWORD) {
	DWORD idleMs = 0;
	if (!g_saverOn && !IsDesktopUnavailable() &&
        GetTickCount64() >= g_resumeGraceUntil &&
        IsIdle(&idleMs) &&
        idleMs >= (DWORD)g_settings.idleTimeoutSec * 1000) {
		ShowSaver();
	}
}

bool IsIdle(DWORD* outIdleMs) {
	LASTINPUTINFO lii{ sizeof(lii) };
	if (!GetLastInputInfo(&lii))
		return false;
	*outIdleMs = GetTickCount() - lii.dwTime;
	return true;
}

// ================= window class =================
LRESULT CALLBACK SaverWndProc(HWND hWnd, UINT uMsg,
                              WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_NCHITTEST:
		return HTTRANSPARENT;   // extra safety: never take clicks
	case WM_DISPLAYCHANGE:
		// Resolution changed while active: rebuild next frame.
		if (g_saverOn)
			DestroyBackBuffer();
		break;
	}
	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

void RegisterSaverClass() {
	if (g_classRegistered)
		return;
	WNDCLASSEXW wc{};
	wc.cbSize        = sizeof(wc);
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = SaverWndProc;
	wc.hInstance     = GetModuleHandleW(nullptr);
	wc.hCursor       = LoadCursorW(nullptr, IDC_ARROW);
	wc.lpszClassName = L"BubbleGlassSaver";
	if (RegisterClassExW(&wc))
		g_classRegistered = true;
}


void UnregisterSaverClass() {
	if (g_classRegistered) {
		UnregisterClassW(L"BubbleGlassSaver", GetModuleHandleW(nullptr));
		g_classRegistered = false;
	}
}

// Session and power notifications arrive on the UI thread that owns the
// saver window, so state changes do not need cross-thread synchronization.
LRESULT CALLBACK ControlWndProc(HWND hWnd, UINT message,
                                WPARAM wParam, LPARAM lParam) {
    bool handled = false;
    bool previouslyUnavailable = IsDesktopUnavailable();

    if (message == WM_WTSSESSION_CHANGE) {
        switch (wParam) {
            case WTS_SESSION_LOCK:
                g_sessionLocked = true;
                handled = true;
                break;
            case WTS_SESSION_UNLOCK:
                g_sessionLocked = false;
                handled = true;
                break;
            case WTS_CONSOLE_DISCONNECT:
            case WTS_REMOTE_DISCONNECT:
                g_sessionDisconnected = true;
                handled = true;
                break;
            case WTS_CONSOLE_CONNECT:
            case WTS_REMOTE_CONNECT:
                g_sessionDisconnected = false;
                handled = true;
                break;
        }
    } else if (message == WM_POWERBROADCAST &&
               wParam == PBT_POWERSETTINGCHANGE) {
        const auto* power =
            reinterpret_cast<const POWERBROADCAST_SETTING*>(lParam);
        if (power && power->DataLength >= sizeof(DWORD) &&
            IsEqualGUID(power->PowerSetting, kConsoleDisplayState)) {
            DWORD state = 1;
            memcpy(&state, power->Data, sizeof(state));
            g_displayOff = state == 0;  // 0 = off, 1 = on, 2 = dimmed
            handled = true;
        }
    }

    if (handled) {
        if (IsDesktopUnavailable()) {
            HideSaver("session-locked/disconnected-or-display-off");
        } else if (previouslyUnavailable) {
            // Avoid reopening immediately after the user unlocks or wakes
            // the screen even when the last-input timestamp is still old.
            g_resumeGraceUntil = GetTickCount64() + 3000;
        }
        if (previouslyUnavailable != IsDesktopUnavailable() ||
            message == WM_WTSSESSION_CHANGE) {
            Wh_Log(L"BubbleGlass visibility: locked=%d disconnected=%d displayOff=%d",
                   g_sessionLocked, g_sessionDisconnected, g_displayOff);
        }
        return message == WM_POWERBROADCAST ? TRUE : 0;
    }

    return DefWindowProcW(hWnd, message, wParam, lParam);
}

void RegisterControlWindow() {
    HINSTANCE instance = GetModuleHandleW(nullptr);
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = ControlWndProc;
    wc.hInstance = instance;
    wc.lpszClassName = L"BubbleGlassControl";
    if (!RegisterClassExW(&wc)) {
        Wh_Log(L"BubbleGlass: RegisterClassExW(control) failed (%lu)",
               GetLastError());
        return;
    }
    g_controlClassRegistered = true;

    // Hidden zero-sized top-level window, following Windhawk fluid-wallpaper.
    // Unlike the saver window, it exists for the entire tool-mod lifetime.
    g_controlWnd = CreateWindowExW(
        WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
        L"BubbleGlassControl", L"", WS_POPUP, 0, 0, 0, 0,
        nullptr, nullptr, instance, nullptr);
    if (!g_controlWnd) {
        Wh_Log(L"BubbleGlass: CreateWindowExW(control) failed (%lu)",
               GetLastError());
        return;
    }

    g_sessionNotificationsRegistered =
        WTSRegisterSessionNotification(g_controlWnd,
                                       NOTIFY_FOR_THIS_SESSION) != FALSE;
    if (!g_sessionNotificationsRegistered) {
        Wh_Log(L"BubbleGlass: WTS session notification failed (%lu)",
               GetLastError());
    }

    g_displayPowerNotification =
        RegisterPowerSettingNotification(g_controlWnd, &kConsoleDisplayState,
                                          DEVICE_NOTIFY_WINDOW_HANDLE);
    if (!g_displayPowerNotification) {
        Wh_Log(L"BubbleGlass: console display notification failed (%lu)",
               GetLastError());
    }
}

void UnregisterControlWindow() {
    if (g_sessionNotificationsRegistered) {
        WTSUnRegisterSessionNotification(g_controlWnd);
        g_sessionNotificationsRegistered = false;
    }
    if (g_displayPowerNotification) {
        UnregisterPowerSettingNotification(g_displayPowerNotification);
        g_displayPowerNotification = nullptr;
    }
    if (g_controlWnd) {
        DestroyWindow(g_controlWnd);
        g_controlWnd = nullptr;
    }
    if (g_controlClassRegistered) {
        UnregisterClassW(L"BubbleGlassControl", GetModuleHandleW(nullptr));
        g_controlClassRegistered = false;
    }
}

// ================= back buffer =================
// 32-bit top-down DIB selected into a memory DC, presented with
// UpdateLayeredWindow(ULW_ALPHA) for true per-pixel transparency.
void CreateBackBuffer(int w, int h) {
	DestroyBackBuffer();

	HDC hdcScreen = GetDC(nullptr);
	if (!hdcScreen)
		return;

	g_memDC = CreateCompatibleDC(hdcScreen);
	if (!g_memDC) {
		ReleaseDC(nullptr, hdcScreen);
		return;
	}

	BITMAPINFO bmi{};
	bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth       = w;
	bmi.bmiHeader.biHeight      = -h;
	bmi.bmiHeader.biPlanes      = 1;
	bmi.bmiHeader.biBitCount    = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	g_bitmapBits = nullptr;

	g_hBmp = CreateDIBSection(
	             hdcScreen,
	             &bmi,
	             DIB_RGB_COLORS,
	             &g_bitmapBits,
	             nullptr,
	             0
	         );

	if (g_hBmp && g_bitmapBits) {
		g_oldBmp = static_cast<HBITMAP>(
		               SelectObject(g_memDC, g_hBmp)
		           );
	} else {
		if (g_hBmp) {
			DeleteObject(g_hBmp);
			g_hBmp = nullptr;
		}

		DeleteDC(g_memDC);
		g_memDC = nullptr;
		g_bitmapBits = nullptr;
	}

	ReleaseDC(nullptr, hdcScreen);
}

void DestroyBackBuffer() {
	if (g_memDC) {
		if (g_oldBmp) {
			SelectObject(g_memDC, g_oldBmp);
			g_oldBmp = nullptr;
		}

		if (g_hBmp) {
			DeleteObject(g_hBmp);
			g_hBmp = nullptr;
		}

		DeleteDC(g_memDC);
		g_memDC = nullptr;
	}

	g_bitmapBits = nullptr;
}

// Fast direct clear of the 32-bit PARGB DIB.
void ClearDibPremul(BYTE a, BYTE r, BYTE g, BYTE b) {
	if (!g_bitmapBits || g_vw <= 0 || g_vh <= 0)
		return;

	auto Premul = [a](BYTE c) -> BYTE {
		return static_cast<BYTE>(
		    (static_cast<unsigned>(c) * static_cast<unsigned>(a) + 127u) / 255u
		);
	};

	const BYTE pr = Premul(r);
	const BYTE pg = Premul(g);
	const BYTE pb = Premul(b);

	const DWORD pixel =
	    (static_cast<DWORD>(a)  << 24) |
	    (static_cast<DWORD>(pr) << 16) |
	    (static_cast<DWORD>(pg) << 8)  |
	    static_cast<DWORD>(pb);

	DWORD* dst = static_cast<DWORD*>(g_bitmapBits);

	const size_t pixelCount =
	    static_cast<size_t>(g_vw) *
	    static_cast<size_t>(g_vh);

	std::fill_n(dst, pixelCount, pixel);
}

// ================= bubbles =================
// Uses <random> (mt19937 + distributions) — this resolves the
// clangd "included header random is not used" warning.
Bubble SpawnBubble(bool anywhere, int W, int H) {
	std::uniform_real_distribution<float> u01(0.0f, 1.0f);
	std::uniform_real_distribution<float> uHue(0.0f, 360.0f);
	std::uniform_real_distribution<float> uSpeed(0.75f, 1.55f);
	std::uniform_real_distribution<float> uWob(0.4f, 1.8f);
	std::uniform_real_distribution<float> uFrq(0.5f, 2.1f);
	std::uniform_real_distribution<float> uPh(0.0f, 6.2832f);
	std::uniform_real_distribution<float> uAl(0.65f, 1.0f);

	const float safeW = W > 1 ? static_cast<float>(W) : 1.0f;
	const float safeH = H > 1 ? static_cast<float>(H) : 1.0f;

	float minR = g_settings.minBubbleSize / 2.0f;
	float maxR = g_settings.maxBubbleSize / 2.0f;

	if (minR < 10.0f) minR = 10.0f;
	if (maxR < minR) maxR = minR;

	// Never create a circle so large that its centre cannot fit on screen.
	float screenMaxR = (safeW < safeH ? safeW : safeH) * 0.48f;
	if (screenMaxR < 10.0f) screenMaxR = 10.0f;
	if (maxR > screenMaxR) maxR = screenMaxR;
	if (minR > maxR) minR = maxR;

	float r = maxR;

	if (g_settings.sizeVariation && maxR > minR) {
		// t^2 deliberately creates many small/medium bubbles and fewer huge ones.
		float t = u01(g_rng);
		r = minR + t * t * (maxR - minR);
	}

	Bubble b{};
	b.r = r;

	if (anywhere) {
		float left   = r;
		float right  = safeW - r;
		float top    = r;
		float bottom = safeH - r;

		if (right < left)
			left = right = safeW * 0.5f;
		if (bottom < top)
			top = bottom = safeH * 0.5f;

		b.x = left + u01(g_rng) * (right - left);
		b.y = top + u01(g_rng) * (bottom - top);

		float angle = u01(g_rng) * 6.2831853f;
		float speed = uSpeed(g_rng);
		b.vx = cosf(angle) * speed;
		b.vy = sinf(angle) * speed;
	} else {
		// Classic Windows-Bubbles feel: new bubbles arrive from lower-left.
		float spawnXJitter = safeW * 0.025f;
		if (spawnXJitter > 110.0f)
			spawnXJitter = 110.0f;

		float spawnYJitter = safeH * 0.12f;
		if (spawnYJitter > 160.0f)
			spawnYJitter = 160.0f;

		b.x = r + 4.0f + u01(g_rng) * spawnXJitter;
		b.y = safeH - r - 4.0f - u01(g_rng) * spawnYJitter;

		// Mostly up/right. Screen Y grows downward, hence negative vy.
		float angleDeg = 28.0f + u01(g_rng) * 42.0f;
		float angle = angleDeg * 3.14159265f / 180.0f;
		float speed = uSpeed(g_rng);

		b.vx = cosf(angle) * speed;
		b.vy = -sinf(angle) * speed;
	}

	b.wobAmp  = uWob(g_rng);
	b.wobFreq = uFrq(g_rng);
	b.phase   = uPh(g_rng);
	b.hue     = uHue(g_rng);
	b.alpha   = uAl(g_rng);

	// Size-biased lifetime inside the user-configured range.
	// With 60..240 seconds this yields roughly:
	// small ≈ 60..120, medium ≈ 90..180, large ≈ 180..240.
	float sizeRatio = 1.0f;
	if (maxR > minR)
		sizeRatio = (r - minR) / (maxR - minR);

	if (sizeRatio < 0.0f) sizeRatio = 0.0f;
	if (sizeRatio > 1.0f) sizeRatio = 1.0f;

	float minLife = static_cast<float>(g_settings.minLifetimeSec);
	float maxLife = static_cast<float>(g_settings.maxLifetimeSec);
	float lifeSpan = maxLife - minLife;

	b.life =
	    minLife +
	    sizeRatio * lifeSpan * 0.67f +
	    u01(g_rng) * lifeSpan * 0.33f;

	if (b.life > maxLife)
		b.life = maxLife;

	b.popping = false;
	b.popProgress = 0.0f;

	return b;
}

void SeedBubbles(int width, int height) {
	g_bubbles.clear();
	g_bubbles.reserve(static_cast<size_t>(
	                      g_settings.bubbleCount > 0 ? g_settings.bubbleCount : 0
	                  ));

	// Start with one bubble. The desktop fills progressively from lower-left.
	if (g_settings.bubbleCount > 0)
		g_bubbles.push_back(SpawnBubble(false, width, height));

	g_lastBubbleSpawnTick = GetTickCount64();
}

// ================= render loop =================
void StartRenderLoop() {
	if (!g_saverWnd || g_rendering)
		return;

	QueryPerformanceFrequency(&g_qpcFrequency);

	LARGE_INTEGER nowQpc{};
	QueryPerformanceCounter(&nowQpc);

	// Exact 60 FPS target: about 16.666667 ms total per frame.
	g_frameIntervalQpc =
	    (g_qpcFrequency.QuadPart + 30) / 60;

	g_lastFrameQpc = 0;  // First frame uses nominal 1/60 second.
    g_showQpc = nowQpc.QuadPart;

	// ShowSaver() renders the first frame immediately.
	g_nextFrameQpc =
	    nowQpc.QuadPart + g_frameIntervalQpc;

	g_rendering = true;
}

void StopRenderLoop() {
	g_rendering = false;
	g_lastFrameQpc = 0;
    g_showQpc = 0;
	g_nextFrameQpc = 0;

	if (g_frameTimer)
		CancelWaitableTimer(g_frameTimer);
}

Color HslToColor(float h, float s, float l, BYTE a) {
	h = fmodf(h, 360.0f);
	if (h < 0.0f) h += 360.0f;
	h /= 360.0f;
	float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
	float p = 2.0f * l - q;
	auto hue2rgb = [&](float t) -> float {
		if (t < 0.0f) t += 1.0f;
		if (t > 1.0f) t -= 1.0f;
		if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
		if (t < 0.5f)        return q;
		if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
		return p;
	};
	BYTE r = (BYTE)(hue2rgb(h + 1.0f / 3.0f) * 255.0f);
	BYTE g = (BYTE)(hue2rgb(h) * 255.0f);
	BYTE b = (BYTE)(hue2rgb(h - 1.0f / 3.0f) * 255.0f);
	return Color(a, r, g, b);
}

double PerfDeltaMs(
    const LARGE_INTEGER& begin,
    const LARGE_INTEGER& end
) {
	if (g_perf.frequency.QuadPart <= 0)
		return 0.0;

	return
	    static_cast<double>(end.QuadPart - begin.QuadPart) *
	    1000.0 /
	    static_cast<double>(g_perf.frequency.QuadPart);
}

// Optional per-bubble QPC checkpoints; no QPC calls when disabled.
struct DrawProfileCheckpoint {
    bool enabled;
    LARGE_INTEGER previous{};

    explicit DrawProfileCheckpoint(bool active) : enabled(active) {
        if (enabled)
            QueryPerformanceCounter(&previous);
    }

    void Mark(double& accumulatedMs) {
        if (!enabled)
            return;
        LARGE_INTEGER now{};
        QueryPerformanceCounter(&now);
        accumulatedMs += PerfDeltaMs(previous, now);
        previous = now;
    }
};

void ResetPerformanceStats() {
	g_perf = PerformanceStats{};

	QueryPerformanceFrequency(&g_perf.frequency);

	g_perf.textLine1 = L"FPS: collecting...";
	g_perf.textLine2 = L"Work / Wait: collecting...";
	g_perf.textLine3 = L"Physics / Draw / Present: collecting...";
	g_perf.textLine4 = L"Clear / Surface / HUD: collecting...";
}

void BeginPerformanceFrame() {
	if (!g_settings.showPerformanceStats &&
	        !g_settings.logPerformanceStats) {
		return;
	}

	if (g_perf.frequency.QuadPart <= 0)
		QueryPerformanceFrequency(&g_perf.frequency);

	g_perf.current = PerfBreakdown{};

	QueryPerformanceCounter(&g_perf.renderStart);
}

void EndPerformanceFrame() {
	if (!g_settings.showPerformanceStats &&
	        !g_settings.logPerformanceStats) {
		return;
	}

	LARGE_INTEGER now{};
	QueryPerformanceCounter(&now);

	if (g_perf.frequency.QuadPart <= 0)
		return;

	const double renderMs =
	    PerfDeltaMs(g_perf.renderStart, now);

	double frameMs = 0.0;

	if (g_perf.lastPresent.QuadPart != 0) {
		frameMs =
		    PerfDeltaMs(g_perf.lastPresent, now);
	}

	g_perf.lastPresent = now;

	if (frameMs > 0.1 && frameMs < 2000.0) {
		const int index = g_perf.sampleIndex;

		g_perf.frameMs[index] = frameMs;
		g_perf.renderMs[index] = renderMs;
		g_perf.breakdown[index] = g_perf.current;

		g_perf.sampleIndex =
		    (g_perf.sampleIndex + 1) % 120;

		if (g_perf.sampleCount < 120)
			++g_perf.sampleCount;
	}

	const ULONGLONG tickNow = GetTickCount64();

	if (g_perf.sampleCount <= 0 ||
	        (g_perf.lastSummaryTick != 0 &&
	         tickNow - g_perf.lastSummaryTick < 500)) {
		return;
	}

	g_perf.lastSummaryTick = tickNow;

	double sumFrame = 0.0;
	double sumRender = 0.0;
	double maxFrame = 0.0;
	double maxRender = 0.0;

	PerfBreakdown sum{};

	for (int i = 0; i < g_perf.sampleCount; ++i) {
		const double f = g_perf.frameMs[i];
		const double r = g_perf.renderMs[i];

		sumFrame += f;
		sumRender += r;

		if (f > maxFrame)
			maxFrame = f;

		if (r > maxRender)
			maxRender = r;

		const PerfBreakdown& p =
		    g_perf.breakdown[i];

		sum.physicsMs    += p.physicsMs;
        sum.detail.setupMs += p.detail.setupMs;
        sum.detail.rainbowMs += p.detail.rainbowMs;
        sum.detail.rimMs += p.detail.rimMs;
        sum.detail.highlightMs += p.detail.highlightMs;
        sum.detail.shineMs += p.detail.shineMs;
        sum.detail.lowerMs += p.detail.lowerMs;
        sum.detail.popMs += p.detail.popMs;
		sum.surfaceMs    += p.surfaceMs;
		sum.clearMs      += p.clearMs;
		sum.bubbleDrawMs += p.bubbleDrawMs;
		sum.hudMs        += p.hudMs;
		sum.gfxFinishMs  += p.gfxFinishMs;
		sum.presentMs    += p.presentMs;
	}

	const double n =
	    static_cast<double>(g_perf.sampleCount);

	g_perf.avgFrameMs = sumFrame / n;
	g_perf.avgRenderMs = sumRender / n;

	g_perf.avg.physicsMs    = sum.physicsMs / n;
    g_perf.avg.detail.setupMs = sum.detail.setupMs / n;
    g_perf.avg.detail.rainbowMs = sum.detail.rainbowMs / n;
    g_perf.avg.detail.rimMs = sum.detail.rimMs / n;
    g_perf.avg.detail.highlightMs = sum.detail.highlightMs / n;
    g_perf.avg.detail.shineMs = sum.detail.shineMs / n;
    g_perf.avg.detail.lowerMs = sum.detail.lowerMs / n;
    g_perf.avg.detail.popMs = sum.detail.popMs / n;
	g_perf.avg.surfaceMs    = sum.surfaceMs / n;
	g_perf.avg.clearMs      = sum.clearMs / n;
	g_perf.avg.bubbleDrawMs = sum.bubbleDrawMs / n;
	g_perf.avg.hudMs        = sum.hudMs / n;
	g_perf.avg.gfxFinishMs  = sum.gfxFinishMs / n;
	g_perf.avg.presentMs    = sum.presentMs / n;

	g_perf.avgWaitMs =
	    g_perf.avgFrameMs - g_perf.avgRenderMs;

	if (g_perf.avgWaitMs < 0.0)
		g_perf.avgWaitMs = 0.0;

	double variance = 0.0;

	for (int i = 0; i < g_perf.sampleCount; ++i) {
		const double d =
		    g_perf.frameMs[i] -
		    g_perf.avgFrameMs;

		variance += d * d;
	}

	variance /= n;

	g_perf.jitterMs = sqrt(variance);
	g_perf.maxFrameMs = maxFrame;
	g_perf.maxRenderMs = maxRender;

	g_perf.fps =
	    g_perf.avgFrameMs > 0.0
	    ? 1000.0 / g_perf.avgFrameMs
	    : 0.0;

	wchar_t line1[256] {};
	wchar_t line2[256] {};
	wchar_t line3[256] {};
	wchar_t line4[256] {};

	std::swprintf(
	    line1,
	    sizeof(line1) / sizeof(line1[0]),
	    L"FPS %.1f   Frame %.2f ms   Jitter %.2f ms",
	    g_perf.fps,
	    g_perf.avgFrameMs,
	    g_perf.jitterMs
	);

	std::swprintf(
	    line2,
	    sizeof(line2) / sizeof(line2[0]),
	    L"Work %.2f ms   Wait %.2f ms   Bubbles %zu",
	    g_perf.avgRenderMs,
	    g_perf.avgWaitMs,
	    g_bubbles.size()
	);

	std::swprintf(
	    line3,
	    sizeof(line3) / sizeof(line3[0]),
	    L"Physics %.2f   Draw %.2f   Present %.2f ms",
	    g_perf.avg.physicsMs,
	    g_perf.avg.bubbleDrawMs,
	    g_perf.avg.presentMs
	);

	std::swprintf(
	    line4,
	    sizeof(line4) / sizeof(line4[0]),
	    L"Clear %.2f   Surface %.2f   HUD %.2f ms",
	    g_perf.avg.clearMs,
	    g_perf.avg.surfaceMs + g_perf.avg.gfxFinishMs,
	    g_perf.avg.hudMs
	);

	g_perf.textLine1 = line1;
	g_perf.textLine2 = line2;
	g_perf.textLine3 = line3;
	g_perf.textLine4 = line4;

	if (g_settings.logPerformanceStats &&
	        (g_perf.lastLogTick == 0 ||
	         tickNow - g_perf.lastLogTick >= 1000)) {

		g_perf.lastLogTick = tickNow;

		Wh_Log(
		    L"BubbleGlass PERF: "
		    L"FPS=%.1f frame=%.2fms work=%.2fms wait=%.2fms "
		    L"physics=%.2fms clear=%.2fms draw=%.2fms "
		    L"surface=%.2fms hud=%.2fms present=%.2fms "
		    L"jitter=%.2fms maxFrame=%.2fms maxWork=%.2fms "
		    L"bubbles=%zu",

		    g_perf.fps,
		    g_perf.avgFrameMs,
		    g_perf.avgRenderMs,
		    g_perf.avgWaitMs,
		    g_perf.avg.physicsMs,
		    g_perf.avg.clearMs,
		    g_perf.avg.bubbleDrawMs,
		    g_perf.avg.surfaceMs + g_perf.avg.gfxFinishMs,
		    g_perf.avg.hudMs,
		    g_perf.avg.presentMs,
		    g_perf.jitterMs,
		    g_perf.maxFrameMs,
		    g_perf.maxRenderMs,
		    g_bubbles.size()
		);

        if (g_settings.profileBubbleDraw) {
            const BubbleDrawDetails& d = g_perf.avg.detail;
            const double measured = d.setupMs + d.rainbowMs + d.rimMs +
                d.highlightMs + d.shineMs + d.lowerMs + d.popMs;
            Wh_Log(
                L"BubbleGlass DRAW: setup=%.2fms rainbow=%.2fms "
                L"rim=%.2fms highlight=%.2fms shine=%.2fms "
                L"lower=%.2fms pop=%.2fms measured=%.2fms "
                L"drawTotal=%.2fms arcs=%d bubbles=%zu",
                d.setupMs, d.rainbowMs, d.rimMs, d.highlightMs,
                d.shineMs, d.lowerMs, d.popMs, measured,
                g_perf.avg.bubbleDrawMs,
                g_settings.iridescenceArcCount, g_bubbles.size());
        }
	}
}

void DrawPerformanceStats(Graphics& gfx, float fadeAlpha) {
	if (!g_settings.showPerformanceStats || fadeAlpha <= 0.01f)
		return;

	FontFamily family(L"Consolas");
	Font font(&family, 30.0f, FontStyleRegular, UnitPixel);
	StringFormat format;
	format.SetAlignment(StringAlignmentNear);
	format.SetLineAlignment(StringAlignmentNear);

	const REAL x = 42.0f;
	const REAL y = 42.0f;
	const REAL w = 920.0f;
	const REAL h = 170.0f;

	SolidBrush bg(Color(
	                  static_cast<BYTE>(145.0f * fadeAlpha),
	                  0, 0, 0));
	gfx.FillRectangle(&bg, RectF(x - 14.0f, y - 10.0f, w, h));

	SolidBrush textBrush(Color(
	                         static_cast<BYTE>(235.0f * fadeAlpha),
	                         255, 255, 255));

	const std::wstring& line1 = g_perf.textLine1.empty()
	                            ? std::wstring(L"FPS: collecting...")
	                            : g_perf.textLine1;
	const std::wstring& line2 = g_perf.textLine2.empty()
	                            ? std::wstring(L"Frame: --  Render: --  Jitter: --")
	                            : g_perf.textLine2;

	gfx.DrawString(line1.c_str(), -1, &font,
	               RectF(x, y, w - 28.0f, 38.0f), &format, &textBrush);
	gfx.DrawString(line2.c_str(), -1, &font,
	               RectF(x, y + 38.0f, w - 28.0f, 38.0f), &format, &textBrush);
	gfx.DrawString(g_perf.textLine3.c_str(), -1,
	               &font, RectF(x, y + 76.0f, w - 28.0f, 38.0f), &format, &textBrush);
	gfx.DrawString(g_perf.textLine4.c_str(), -1, &font,
	               RectF(x, y + 114.0f, w - 28.0f, 38.0f), &format, &textBrush);
}

void DrawBubble(
    Graphics& gfx,
    const Bubble& b,
    float fadeAlpha,
    double animationSeconds
) {

	if (fadeAlpha <= 0.01f)
		return;

    DrawProfileCheckpoint profile(
        g_settings.profileBubbleDraw && g_settings.logPerformanceStats);

	float popP = b.popping ? b.popProgress : 0.0f;
	if (popP < 0.0f) popP = 0.0f;
	if (popP > 1.0f) popP = 1.0f;

	// Pop animation: the membrane stretches outward, flashes, then vanishes.
	float popEase = 1.0f - (1.0f - popP) * (1.0f - popP);
	float popScale = 1.0f + g_settings.PopGrowth() * popEase;
	float popFade = b.popping ? (1.0f - popP) : 1.0f;
	float popFlash = b.popping ? sinf(popP * 3.14159265f) : 0.0f;

	float globalA =
	    b.alpha *
	    (g_settings.bubbleOpacity / 100.0f) *
	    fadeAlpha *
	    popFade;

	if (globalA <= 0.005f)
		return;

	auto Alpha = [globalA](float value) -> BYTE {
		float a = value * globalA;
		if (a < 0.0f) a = 0.0f;
		if (a > 255.0f) a = 255.0f;
		return static_cast<BYTE>(a + 0.5f);
	};

	const REAL r = b.r * popScale;
	const REAL x = b.x;
	const REAL y = b.y;

	// Seconds elapsed since the saver appeared (high-resolution, double).
    // Avoid float precision loss from the Windows system uptime.
	// Tiny organic deformation. Large bubbles stay calmer than small ones.
	float sizeCalm = 1.0f / (1.0f + r * 0.0022f);
	float wobble =
	    static_cast<float>(std::sin(
            animationSeconds * 1.25 * b.wobFreq + b.phase)) *
	    0.026f * sizeCalm;

	wobble += popFlash * 0.018f;

	REAL rx = r * (1.0f + wobble);
	REAL ry = r * (1.0f - wobble);

	RectF rect(
	    x - rx,
	    y - ry,
	    rx * 2.0f,
	    ry * 2.0f
	);

	REAL rootR = sqrtf(r > 1.0f ? r : 1.0f);

	// Optional subtle lower-right shadow/reflection. It is an arc, not a filled
	// disc, so the live desktop/video remains visible through the membrane.
	if (g_settings.showShadows) {
		REAL shadowOffset = 1.5f + rootR * 0.28f;
		if (shadowOffset > 14.0f)
			shadowOffset = 14.0f;

		REAL shadowWidth = 1.0f + rootR * 0.16f;
		if (shadowWidth > 5.0f)
			shadowWidth = 5.0f;

		g_bubbleGdi->shadowPen.SetColor(
		    Color(Alpha(30.0f), 0, 0, 0)
		);
		g_bubbleGdi->shadowPen.SetWidth(shadowWidth);

		gfx.DrawArc(
		    &g_bubbleGdi->shadowPen,
		    rect.X + shadowOffset,
		    rect.Y + shadowOffset,
		    rect.Width,
		    rect.Height,
		    18.0f,
		    145.0f
		);
	}

	// Slowly travelling thin-film interference colours. The arcs are deliberately
	// asymmetric so the bubble doesn't look like a neon ring.
    double colourTime =
        animationSeconds * 1000.0 * g_settings.ColorCycle();
    double colourTravel = colourTime * 0.0055;
    float hueBreath =
        static_cast<float>(std::sin(colourTime * 0.00022 + b.phase) * 24.0);
    float baseHue = fmodf(b.hue + hueBreath + 360.0f, 360.0f);

	REAL filmWidth = 1.15f + rootR * 0.19f;
	if (filmWidth > 5.2f) filmWidth = 5.2f;
	filmWidth *= 1.0f + popFlash * 0.55f;

    profile.Mark(g_perf.current.detail.setupMs);
	if (g_settings.iridescence) {
		struct FilmArc {
			float hueOffset;
			float angleOffset;
			float sweep;
			float alpha;
		};

		static constexpr FilmArc arcs[] = {
			{   0.0f,   8.0f, 82.0f, 142.0f },
			{ 112.0f, 126.0f, 70.0f, 118.0f },
			{ 226.0f, 232.0f, 88.0f, 132.0f },
			{ 308.0f, 326.0f, 48.0f,  92.0f },
		};

        // GDI+ receives a bounded float angle even after long runs.
        float rotation = static_cast<float>(
            std::fmod(b.phase * 57.2958 + colourTravel, 360.0));

        // Keep the full four-arc look by default. When two arcs are
        // requested, place them on opposing sides rather than adjacent.
        g_bubbleGdi->irisPen.SetWidth(filmWidth);
        for (int i = 0; i < g_settings.iridescenceArcCount; ++i) {
            const FilmArc& arc =
                arcs[g_settings.iridescenceArcCount == 2 ? i * 2 : i];
			    float hue = fmodf(baseHue + arc.hueOffset, 360.0f);
			    Color c = HslToColor(
			        hue,
			        0.92f,
			        0.68f,
			        Alpha(arc.alpha + popFlash * 72.0f)
			    );

			    g_bubbleGdi->irisPen.SetColor(c);

			    gfx.DrawArc(
			        &g_bubbleGdi->irisPen,
			        rect.X,
			        rect.Y,
			        rect.Width,
			        rect.Height,
			        rotation + arc.angleOffset,
			        arc.sweep
			    );
            }
		}
        profile.Mark(g_perf.current.detail.rainbowMs);

		// Neutral membrane rim. Kept subtle so the colour arcs remain dominant.
		REAL rimWidth = 0.85f + rootR * 0.105f;
		if (rimWidth > 3.1f) rimWidth = 3.1f;
		rimWidth *= 1.0f + popFlash * 1.0f;

		g_bubbleGdi->rimPen.SetColor(
		    Color(
		        Alpha(78.0f + popFlash * 125.0f),
		        238,
		        248,
		        255
		    )
		);

		g_bubbleGdi->rimPen.SetWidth(rimWidth);

		gfx.DrawEllipse(
		    &g_bubbleGdi->rimPen,
		    rect
		);
        profile.Mark(g_perf.current.detail.rimMs);

		// Curved specular highlight in the upper-left quadrant. This reads more like
		// reflected light on a spherical membrane than a large opaque white blob.
		REAL highlightWidth = 1.25f + rootR * 0.13f;
		if (highlightWidth > 3.8f) highlightWidth = 3.8f;

		g_bubbleGdi->highlightPen.SetColor(
		    Color(
		        Alpha(188.0f + popFlash * 50.0f),
		        255,
		        255,
		        255
		    )
		);

		g_bubbleGdi->highlightPen.SetWidth(highlightWidth);

		float highlightStart = 205.0f + sinf(b.phase) * 12.0f;
		gfx.DrawArc(
		    &g_bubbleGdi->highlightPen,
		    rect.X + rx * 0.035f,
		    rect.Y + ry * 0.035f,
		    rect.Width - rx * 0.070f,
		    rect.Height - ry * 0.070f,
		    highlightStart,
		    54.0f
		);
        profile.Mark(g_perf.current.detail.highlightMs);

		// Tiny hot spot near the highlight. Scale it gently instead of turning it
		// into a huge solid patch on very large bubbles.
		REAL dotR = 1.6f + rootR * 0.17f;
		if (dotR > r * 0.065f) dotR = r * 0.065f;
		if (dotR < 1.1f) dotR = 1.1f;

		g_bubbleGdi->shineBrush.SetColor(
		    Color(
		        Alpha(222.0f),
		        255,
		        255,
		        255
		    )
		);

		gfx.FillEllipse(
		    &g_bubbleGdi->shineBrush,
		    x - rx * 0.31f - dotR,
		    y - ry * 0.34f - dotR,
		    dotR * 2.0f,
		    dotR * 2.0f
		);
        profile.Mark(g_perf.current.detail.shineMs);

		// Very faint opposite-side reflection gives the sphere a little depth.
		g_bubbleGdi->lowerReflectionPen.SetColor(
		    Color(
		        Alpha(44.0f),
		        210,
		        235,
		        255
		    )
		);

		g_bubbleGdi->lowerReflectionPen.SetWidth(
		    rimWidth * 0.82f
		);

		gfx.DrawArc(
		    &g_bubbleGdi->lowerReflectionPen,
		    rect.X + rx * 0.055f,
		    rect.Y + ry * 0.055f,
		    rect.Width - rx * 0.110f,
		    rect.Height - ry * 0.110f,
		    38.0f,
		    44.0f
		);
        profile.Mark(g_perf.current.detail.lowerMs);

		// Pop: a fast expanding white ring, using the same live bubble geometry.
		if (b.popping && popFlash > 0.02f) {
			REAL extra = r * (0.012f + popFlash * 0.040f);
			RectF popRect(
			    rect.X - extra,
			    rect.Y - extra,
			    rect.Width + extra * 2.0f,
			    rect.Height + extra * 2.0f
			);

			g_bubbleGdi->flashPen.SetColor(
			    Color(
			        Alpha(220.0f * popFlash),
			        255,
			        255,
			        255
			    )
			);

			g_bubbleGdi->flashPen.SetWidth(
			    rimWidth * (1.0f + popFlash * 1.35f)
			);

			gfx.DrawEllipse(
			    &g_bubbleGdi->flashPen,
			    popRect
			);
		}
    profile.Mark(g_perf.current.detail.popMs);
	}

	void RenderFrame() {
		if (!g_saverOn || !g_saverWnd)
			return;

		BeginPerformanceFrame();

		const bool perfEnabled =
		    g_settings.showPerformanceStats ||
		    g_settings.logPerformanceStats;

		LARGE_INTEGER perfMark =
		    g_perf.renderStart;

		auto PerfMark = [&](double& destination) {
			if (!perfEnabled)
				return;

			LARGE_INTEGER q{};
			QueryPerformanceCounter(&q);

			destination =
			    PerfDeltaMs(perfMark, q);

			perfMark = q;
		};

		ULONGLONG now64 = GetTickCount64();

        // Use QPC for physics and animation. GetTickCount64 can advance in
        // coarse ~15.6 ms steps, even with an accurate QPC frame pacer.
        LARGE_INTEGER nowQpc{};
        QueryPerformanceCounter(&nowQpc);
        float dt = 1.0f / 60.0f;
        double animationSeconds = 0.0;
        if (g_qpcFrequency.QuadPart > 0) {
            if (g_lastFrameQpc != 0) {
                dt = static_cast<float>(
                    static_cast<double>(nowQpc.QuadPart - g_lastFrameQpc) /
                    static_cast<double>(g_qpcFrequency.QuadPart));
                // Avoid jumps after breakpoints or a stalled renderer.
                if (dt < 0.001f)
                    dt = 0.001f;
                if (dt > 0.500f)
                    dt = 0.500f;
            }
            if (g_showQpc != 0) {
                animationSeconds =
                    static_cast<double>(nowQpc.QuadPart - g_showQpc) /
                    static_cast<double>(g_qpcFrequency.QuadPart);
            }
        }
        g_lastFrameQpc = nowQpc.QuadPart;

		float t =
		    static_cast<float>(now64 - g_showTick) /
		    static_cast<float>(FADE_IN_MS);

		if (t > 1.0f) t = 1.0f;
		if (t < 0.0f) t = 0.0f;

		g_fade = 1.0f - (1.0f - t) * (1.0f - t);

		float drift = g_settings.Drift();

		// Historical velocity values were tuned around 60 updates/second.
		float frameScale = dt * 60.0f;

		// Add one bubble at a time until the configured target is reached.
		// When an old bubble expires, the same mechanism replenishes it later.
		if (static_cast<int>(g_bubbles.size()) < g_settings.bubbleCount &&
		        now64 - g_lastBubbleSpawnTick >=
		        static_cast<ULONGLONG>(g_settings.spawnIntervalMs)) {
			g_bubbles.push_back(SpawnBubble(false, g_vw, g_vh));
			g_lastBubbleSpawnTick = now64;
		}

		// Integrate positions, age bubbles, and bounce at all four walls.
		// When life reaches zero, the bubble switches into a short visible pop state.
		for (auto& b : g_bubbles) {
			if (!b.popping) {
				// Optional smooth air current. It gently bends trajectories without
				// replacing the existing billiard-style velocity/collision system.
				if (g_settings.turbulence > 0) {
					float turbulenceAmount =
					    g_settings.turbulence / 100.0f;

					float windX =
                        static_cast<float>(std::sin(
                            animationSeconds * 0.31 + b.phase)) +
                        static_cast<float>(std::sin(
                            animationSeconds * 0.17 * b.wobFreq +
                            b.phase * 1.73)) * 0.55f;

					float windY =
                        static_cast<float>(std::cos(
                            animationSeconds * 0.27 +
                            b.phase * 0.83)) +
                        static_cast<float>(std::sin(
                            animationSeconds * 0.13 * b.wobFreq +
                            b.phase * 2.11)) * 0.45f;

					float windAcceleration =
					    turbulenceAmount * 0.0065f * frameScale;

					b.vx += windX * windAcceleration;
					b.vy += windY * windAcceleration;

					// Keep turbulence from accelerating a bubble forever.
					float speedSq = b.vx * b.vx + b.vy * b.vy;
					float maxSpeed = 2.3f + turbulenceAmount * 1.7f;

					if (speedSq > maxSpeed * maxSpeed) {
						float speed = sqrtf(speedSq);
						if (speed > 0.0001f) {
							float scale = maxSpeed / speed;
							b.vx *= scale;
							b.vy *= scale;
						}
					}
				}

				b.x += b.vx * drift * frameScale;
				b.y += b.vy * drift * frameScale;

				// Tiny organic side drift. This is not a second velocity integration.
                b.x += static_cast<float>(std::sin(
                    animationSeconds * b.wobFreq + b.phase)) *
                    b.wobAmp * 0.08f * frameScale;

				b.life -= dt;

				if (b.life <= 0.0f) {
					b.life = 0.0f;
					b.popping = true;
					b.popProgress = g_settings.popEnabled ? 0.0f : 1.0f;
				}
			} else {
				// Let a popping bubble keep a little of its momentum instead of
				// freezing in place during the membrane burst.
				b.x += b.vx * drift * frameScale * 0.30f;
				b.y += b.vy * drift * frameScale * 0.30f;

				if (g_settings.popEnabled) {
					float popDt = dt;
					if (popDt > 0.050f)
						popDt = 0.050f;

					float popDuration =
					    g_settings.PopDurationSec();

					if (popDuration < 0.050f)
						popDuration = 0.050f;

					b.popProgress += popDt / popDuration;
				} else {
					b.popProgress = 1.0f;
				}
			}

			// Edge behaviour is configurable: classic bounce, or seamless wrap.
			if (g_settings.wallCollisions) {
				if (b.x - b.r < 0.0f) {
					b.x = b.r;
					b.vx = fabsf(b.vx);
				} else if (b.x + b.r > static_cast<float>(g_vw)) {
					b.x = static_cast<float>(g_vw) - b.r;
					b.vx = -fabsf(b.vx);
				}

				if (b.y - b.r < 0.0f) {
					b.y = b.r;
					b.vy = fabsf(b.vy);
				} else if (b.y + b.r > static_cast<float>(g_vh)) {
					b.y = static_cast<float>(g_vh) - b.r;
					b.vy = -fabsf(b.vy);
				}
			} else {
				if (b.x < -b.r)
					b.x = static_cast<float>(g_vw) + b.r;
				else if (b.x > static_cast<float>(g_vw) + b.r)
					b.x = -b.r;

				if (b.y < -b.r)
					b.y = static_cast<float>(g_vh) + b.r;
				else if (b.y > static_cast<float>(g_vh) + b.r)
					b.y = -b.r;
			}
		}

		// Remove bubbles only after their visible pop animation has completed.
		// Reset the spawn clock so a replacement arrives after a short pause.
		bool removedPoppedBubble = false;
		for (size_t i = 0; i < g_bubbles.size();) {
			if (g_bubbles[i].popping && g_bubbles[i].popProgress >= 1.0f) {
				g_bubbles.erase(g_bubbles.begin() + i);
				removedPoppedBubble = true;
			} else {
				++i;
			}
		}

		if (removedPoppedBubble)
			g_lastBubbleSpawnTick = now64;

		// Elastic bubble-to-bubble collisions.
		// Equal collision mass gives the lively "billiard-ball" reaction used by
		// classic Bubbles-style implementations, while radii still differ visually.
		if (g_settings.bubbleCollisions) {
			const size_t bubbleCount = g_bubbles.size();
			for (size_t i = 0; i < bubbleCount; ++i) {
				for (size_t j = i + 1; j < bubbleCount; ++j) {
					Bubble& a = g_bubbles[i];
					Bubble& b = g_bubbles[j];

					// A burst membrane no longer participates in billiard physics.
					if (a.popping || b.popping)
						continue;

					float dx = b.x - a.x;
					float dy = b.y - a.y;
					float minDist = a.r + b.r;
					float distSq = dx * dx + dy * dy;

					if (distSq >= minDist * minDist)
						continue;

					float dist;
					float nx;
					float ny;

					if (distSq > 0.0001f) {
						dist = sqrtf(distSq);
						nx = dx / dist;
						ny = dy / dist;
					} else {
						dist = 0.0f;
						nx = 1.0f;
						ny = 0.0f;
					}

					// Separate overlapping circles equally so they don't stick together.
					float overlap = minDist - dist;
					float correction = overlap * 0.5f + 0.01f;

					a.x -= nx * correction;
					a.y -= ny * correction;
					b.x += nx * correction;
					b.y += ny * correction;

					float rvx = b.vx - a.vx;
					float rvy = b.vy - a.vy;
					float velocityAlongNormal = rvx * nx + rvy * ny;

					// Already moving apart: positional correction is enough.
					if (velocityAlongNormal >= 0.0f)
						continue;

					// Equal-mass elastic impulse, very slightly damped.
					float impulse =
					    -(1.0f + COLLISION_RESTITUTION) *
					    velocityAlongNormal * 0.5f;

					float impulseX = impulse * nx;
					float impulseY = impulse * ny;

					a.vx -= impulseX;
					a.vy -= impulseY;
					b.vx += impulseX;
					b.vy += impulseY;
				}
			}
		}

		// Collision separation can push circles a few pixels beyond an edge.
		if (g_settings.wallCollisions) {
			for (auto& b : g_bubbles) {
				if (b.popping)
					continue;

				if (b.x - b.r < 0.0f) {
					b.x = b.r;
					b.vx = fabsf(b.vx);
				} else if (b.x + b.r > static_cast<float>(g_vw)) {
					b.x = static_cast<float>(g_vw) - b.r;
					b.vx = -fabsf(b.vx);
				}

				if (b.y - b.r < 0.0f) {
					b.y = b.r;
					b.vy = fabsf(b.vy);
				} else if (b.y + b.r > static_cast<float>(g_vh)) {
					b.y = static_cast<float>(g_vh) - b.r;
					b.vy = -fabsf(b.vy);
				}
			}
		}

		PerfMark(g_perf.current.physicsMs);

		if (!g_memDC)
			CreateBackBuffer(g_vw, g_vh);
		if (!g_memDC)
			return;

		{
			Bitmap surface(
			    g_vw,
			    g_vh,
			    g_vw * 4,
			    PixelFormat32bppPARGB,
			    static_cast<BYTE*>(g_bitmapBits)
			);

			Graphics gfx(&surface);

			gfx.SetSmoothingMode(SmoothingModeAntiAlias);
			gfx.SetCompositingQuality(CompositingQualityHighSpeed);
			gfx.SetPixelOffsetMode(PixelOffsetModeHighSpeed);

			// Bitmap/Graphics + GDI+ setup.
			PerfMark(g_perf.current.surfaceMs);

			BYTE dimA = static_cast<BYTE>(
			                std::lround(
			                    static_cast<float>(g_settings.dimPercent) *
			                    255.0f / 100.0f * g_fade
			                )
			            );

			// Jetzt misst clearMs wirklich fast nur noch den Full-Screen-Clear.
			ClearDibPremul(dimA, 4, 6, 15);
			PerfMark(g_perf.current.clearMs);

			for (const auto& b : g_bubbles)
				DrawBubble(gfx, b, g_fade, animationSeconds);

			PerfMark(g_perf.current.bubbleDrawMs);

			DrawPerformanceStats(gfx, g_fade);
			PerfMark(g_perf.current.hudMs);
		}

		// Time destruction/finalization of the temporary GDI+ Graphics/Bitmap objects.
		PerfMark(g_perf.current.gfxFinishMs);

		POINT ptSrc{ 0, 0 };
		SIZE  sz{ g_vw, g_vh };
		BLENDFUNCTION bf{};
		bf.BlendOp             = AC_SRC_OVER;
		bf.BlendFlags          = 0;
		bf.SourceConstantAlpha = 255;         // per-pixel alpha in DIB
		bf.AlphaFormat         = AC_SRC_ALPHA;

		UpdateLayeredWindow(
		    g_saverWnd, nullptr, nullptr, &sz,
		    g_memDC, &ptSrc, 0, &bf, ULW_ALPHA
		);

		PerfMark(g_perf.current.presentMs);
		EndPerformanceFrame();
	}

	// ================= show / hide =================
	// Transparent topmost layered window, click-through by design.
	// DWM keeps compositing the live desktop underneath.
	void ShowSaver() {
        if (g_saverOn || IsDesktopUnavailable() ||
            GetTickCount64() < g_resumeGraceUntil || !g_inputWindow)
            return;

		if (g_settings.multiMonitor) {
			g_vx = GetSystemMetrics(SM_XVIRTUALSCREEN);
			g_vy = GetSystemMetrics(SM_YVIRTUALSCREEN);
			g_vw = GetSystemMetrics(SM_CXVIRTUALSCREEN);
			g_vh = GetSystemMetrics(SM_CYVIRTUALSCREEN);
		} else {
			g_vx = 0;
			g_vy = 0;
			g_vw = GetSystemMetrics(SM_CXSCREEN);
			g_vh = GetSystemMetrics(SM_CYSCREEN);
		}
		if (g_vw < 64) g_vw = 64;
		if (g_vh < 64) g_vh = 64;

		RegisterSaverClass();

        // Arm hooks on the input thread before revealing the overlay.
        // Never show an overlay that cannot be dismissed by user input.
        DWORD_PTR armResult = 0;
        UINT_PTR serial = ++g_showSerial;
        if (!SendMessageTimeoutW(g_inputWindow, WM_BUBBLE_INPUT_ARM,
                                 g_settings.dismissDeltaPx,
                                 static_cast<LPARAM>(serial),
                                 SMTO_ABORTIFHUNG | SMTO_BLOCK, 2000,
                                 &armResult) || armResult != TRUE) {
            Wh_Log(L"BubbleGlass: input hooks unavailable; skipping saver");
            g_resumeGraceUntil = GetTickCount64() + 5000;
            return;
        }

		g_saverWnd = CreateWindowExW(
		                 WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST |
		                 WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW,
		                 L"BubbleGlassSaver", L"",
		                 WS_POPUP, g_vx, g_vy, g_vw, g_vh,
		                 nullptr, nullptr, GetModuleHandleW(nullptr), nullptr);
		if (!g_saverWnd) {
            SendMessageTimeoutW(g_inputWindow, WM_BUBBLE_INPUT_DISARM,
                                0, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK,
                                2000, nullptr);
			Wh_Log(L"BubbleGlass: CreateWindowExW failed (%lu)",
			       GetLastError());
			return;
		}

		CreateBackBuffer(g_vw, g_vh);
		SeedBubbles(g_vw, g_vh);
		g_showTick = GetTickCount64();
		g_fade     = 0.0f;
		ResetPerformanceStats();
		g_saverOn  = true;

		ShowWindow(g_saverWnd, SW_SHOWNOACTIVATE);
		SetWindowPos(g_saverWnd, HWND_TOPMOST, 0, 0, 0, 0,
		             SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
		StartRenderLoop();
		RenderFrame();   // first frame immediately (no black flash)

		Wh_Log(L"BubbleGlass shown (%dx%d @ %d,%d, %d bubbles)",
		       g_vw, g_vh, g_vx, g_vy, g_settings.bubbleCount);
	}

	void HideSaver(const char* reason) {
		if (!g_saverOn)
			return;
		g_saverOn = false;
        if (g_inputWindow) {
            SendMessageTimeoutW(g_inputWindow, WM_BUBBLE_INPUT_DISARM,
                                0, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK,
                                2000, nullptr);
        }
		StopRenderLoop();
		if (g_saverWnd) {
			DestroyWindow(g_saverWnd);
			g_saverWnd = nullptr;
		}
		DestroyBackBuffer();
		g_bubbles.clear();
		g_lastBubbleSpawnTick = 0;
		ResetPerformanceStats();
		Wh_Log(L"BubbleGlass hidden (%S)", reason ? reason : "input");
	}

	DWORD WINAPI BubbleUiThread(LPVOID) {
		g_uiThreadId = GetCurrentThreadId();

		// Wichtig: Message Queue für diesen Thread anlegen.
		MSG msg{};
		PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);

		RegisterSaverClass();
        RegisterControlWindow();

		// High-resolution frame timer.
		// Auto-reset timer: one wake-up per armed frame deadline.
		g_frameTimer = CreateWaitableTimerExW(
		                   nullptr,
		                   nullptr,
		                   CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
		                   TIMER_MODIFY_STATE | SYNCHRONIZE
		               );

		if (!g_frameTimer) {
			// Fallback for systems where the high-resolution flag isn't available.
			g_frameTimer = CreateWaitableTimerW(
			                   nullptr,
			                   FALSE,
			                   nullptr
			               );

			if (timeBeginPeriod(1) == TIMERR_NOERROR)
				g_timerPeriodActive = true;
		}

		// Independent, message-only hook thread: never waits on GDI+ rendering.
        g_inputReadyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
        if (g_inputReadyEvent) {
            g_inputThread = CreateThread(nullptr, 0, BubbleInputThread,
                                          nullptr, 0, &g_inputThreadId);
            if (g_inputThread) {
                if (WaitForSingleObject(g_inputReadyEvent, 5000) !=
                    WAIT_OBJECT_0 || !g_inputWindow) {
                    Wh_Log(L"BubbleGlass: input thread did not start correctly");
                }
            } else {
                Wh_Log(L"BubbleGlass: cannot create input thread (%lu)",
                       GetLastError());
            }
        } else {
            Wh_Log(L"BubbleGlass: cannot create input ready event (%lu)",
                   GetLastError());
        }

		// Idle watchdog läuft nun ebenfalls auf diesem Thread.
		g_idleTimer = SetTimer(
		                  nullptr,
		                  0,
		                  250,
		                  IdleTimer
		              );

		if (!g_idleTimer) {
			Wh_Log(L"BubbleGlass: idle timer failed (%lu)", GetLastError());
		}

		if (g_uiReadyEvent) {
			SetEvent(g_uiReadyEvent);
		}

		Wh_Log(
		    L"BubbleGlass UI thread running, thread=%lu",
		    g_uiThreadId
		);

		bool running = true;

		while (running) {
			DWORD waitMs = INFINITE;
			HANDLE waits[1] {};
			DWORD waitCount = 0;

			if (g_saverOn && g_rendering &&
			        g_qpcFrequency.QuadPart > 0) {

				LARGE_INTEGER nowQpc{};
				QueryPerformanceCounter(&nowQpc);

				LONGLONG remaining =
				    g_nextFrameQpc - nowQpc.QuadPart;

				if (remaining <= 0) {
					// Deadline already reached.
					waitMs = 0;
				}
				else if (g_frameTimer) {
					// Convert QPC ticks to relative 100-ns units.
					LONGLONG due100ns =
					    (remaining * 10000000LL) /
					    g_qpcFrequency.QuadPart;

					if (due100ns < 1)
						due100ns = 1;

					LARGE_INTEGER due{};
					due.QuadPart = -due100ns;

					SetWaitableTimer(
					    g_frameTimer,
					    &due,
					    0,
					    nullptr,
					    nullptr,
					    FALSE
					);

					waits[0] = g_frameTimer;
					waitCount = 1;
				}
				else {
					// Very unlikely final fallback.
					LONGLONG remainingMs =
					    (remaining * 1000LL +
					     g_qpcFrequency.QuadPart - 1) /
					    g_qpcFrequency.QuadPart;

					if (remainingMs < 1)
						remainingMs = 1;

					if (remainingMs > 1000)
						remainingMs = 1000;

					waitMs = static_cast<DWORD>(remainingMs);
				}
			}

			MsgWaitForMultipleObjectsEx(
			    waitCount,
			    waitCount ? waits : nullptr,
			    waitMs,
			    QS_ALLINPUT,
			    MWMO_INPUTAVAILABLE
			);

			while (PeekMessageW(
			            &msg,
			            nullptr,
			            0,
			            0,
			            PM_REMOVE)) {

				if (msg.message == WM_QUIT) {
					running = false;
					break;
				}

                if (msg.message == WM_BUBBLE_DISMISS) {
                    // Ignore late events from a previous saver activation.
                    if (g_saverOn &&
                        static_cast<UINT_PTR>(msg.wParam) == g_showSerial) {
                        const char* reason = msg.lParam == 1 ? "keystroke" :
                                             msg.lParam == 2 ? "click/wheel" :
                                                               "mouse-move";
                        HideSaver(reason);
                    }
                    continue;
                }

				if (msg.message == WM_BUBBLE_SETTINGS_CHANGED) {
                    int previousArcCount = g_settings.iridescenceArcCount;
					LoadSettings();
                    if (g_settings.iridescenceArcCount != previousArcCount) {
                        Wh_Log(L"BubbleGlass rainbow arc detail: %d -> %d",
                               previousArcCount,
                               g_settings.iridescenceArcCount);
                    }

					if (g_saverOn) {
						if (static_cast<int>(g_bubbles.size()) >
						        g_settings.bubbleCount) {

							g_bubbles.resize(
							    static_cast<size_t>(
							        g_settings.bubbleCount > 0
							        ? g_settings.bubbleCount
							        : 0
							    )
							);
						}

						if (static_cast<int>(g_bubbles.size()) <
						        g_settings.bubbleCount) {
							g_lastBubbleSpawnTick = 0;
						}
					}

					continue;
				}

				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}

			if (!running)
				break;

			if (g_saverOn && g_rendering &&
			        g_qpcFrequency.QuadPart > 0) {

				LARGE_INTEGER nowQpc{};
				QueryPerformanceCounter(&nowQpc);

				if (nowQpc.QuadPart >= g_nextFrameQpc) {
					RenderFrame();

					// Critical difference from v1.7.2:
					// advance the absolute timeline instead of
					// waiting another 33 ms after rendering.
					g_nextFrameQpc += g_frameIntervalQpc;

					LARGE_INTEGER afterQpc{};
					QueryPerformanceCounter(&afterQpc);

					// If something stalls us for several complete frames,
					// re-anchor once instead of entering a catch-up loop.
					if (afterQpc.QuadPart >
					        g_nextFrameQpc +
					        g_frameIntervalQpc * 3) {

						g_nextFrameQpc =
						    afterQpc.QuadPart +
						    g_frameIntervalQpc;
					}
				}
			}
		}

		// Alles, was diesem Thread gehört, auch hier abbauen.
		HideSaver("thread-exit");

		if (g_idleTimer) {
			KillTimer(nullptr, g_idleTimer);
			g_idleTimer = 0;
		}

        // Hooks and their control window belong to the input thread.
        if (g_inputWindow)
            PostMessageW(g_inputWindow, WM_CLOSE, 0, 0);
        else if (g_inputThreadId)
            PostThreadMessageW(g_inputThreadId, WM_QUIT, 0, 0);
        if (g_inputThread) {
            // On timeout terminate the dedicated tool process, never leave
            // executing hook callbacks in a module about to be unloaded.
            if (WaitForSingleObject(g_inputThread, 5000) != WAIT_OBJECT_0) {
                Wh_Log(L"BubbleGlass: input thread did not exit in time");
                ExitProcess(1);
            }
            CloseHandle(g_inputThread);
            g_inputThread = nullptr;
            g_inputThreadId = 0;
            g_inputWindow = nullptr;
        }
        if (g_inputReadyEvent) {
            CloseHandle(g_inputReadyEvent);
            g_inputReadyEvent = nullptr;
        }

		if (g_frameTimer) {
			CancelWaitableTimer(g_frameTimer);
			CloseHandle(g_frameTimer);
			g_frameTimer = nullptr;
		}

		if (g_timerPeriodActive) {
			timeEndPeriod(1);
			g_timerPeriodActive = false;
		}

		UnregisterControlWindow();
        UnregisterSaverClass();

		g_uiThreadId = 0;

		return 0;
	}

	// ================= Windhawk entry points =================
BOOL WhTool_ModInit() {
	GdiplusStartupInput gdiInput;

		if (GdiplusStartup(
		    &g_gdiplusToken,
		    &gdiInput,
		    nullptr) != Ok) {

			Wh_Log(L"BubbleGlass: GdiplusStartup failed");
			return FALSE;
		}
		g_bubbleGdi = std::make_unique<BubbleGdiResources>();

		std::random_device rd;

		g_rng.seed(
		    rd() ^
		    GetTickCount() ^
		    GetCurrentProcessId()
		);

		LoadSettings();

		g_uiReadyEvent = CreateEventW(
		    nullptr,
		    TRUE,
		    FALSE,
		    nullptr
		);

		if (!g_uiReadyEvent) {
			Wh_Log(
			    L"BubbleGlass: CreateEvent failed (%lu)",
			    GetLastError()
			);

			g_bubbleGdi.reset();

			GdiplusShutdown(g_gdiplusToken);
			g_gdiplusToken = 0;
			return FALSE;
		}

		g_uiThread = CreateThread(
		            nullptr,
		            0,
		            BubbleUiThread,
		            nullptr,
		            0,
		            nullptr
		            );

	if (!g_uiThread) {
	Wh_Log(
		L"BubbleGlass: CreateThread failed (%lu)",
		GetLastError()
	    );

		CloseHandle(g_uiReadyEvent);
		g_uiReadyEvent = nullptr;

		g_bubbleGdi.reset();

		GdiplusShutdown(g_gdiplusToken);
		g_gdiplusToken = 0;

		return FALSE;
	}

	// Warten, bis Message Queue + Timer + Hooks bereit sind.
	WaitForSingleObject(
		g_uiReadyEvent,
		5000
	);

	Wh_Log(
		L"BubbleGlass 1.7.5 RC6 initialized: timeout=%ds, bubbles=%d, rainbowArcs=%d",
		g_settings.idleTimeoutSec,
		g_settings.bubbleCount,
        g_settings.iridescenceArcCount
	);

	return TRUE;
}

void WhTool_ModSettingsChanged() {
	if (g_uiThreadId) {
		PostThreadMessageW(
			g_uiThreadId,
			WM_BUBBLE_SETTINGS_CHANGED,
			0,
			0
		);
	}
}

void WhTool_ModUninit() {
	if (g_uiThreadId) {
		PostThreadMessageW(
			g_uiThreadId,
			WM_QUIT,
			0,
			0
		);
	}

	if (g_uiThread) {
		// Terminate only the dedicated tool process if shutdown stalls.
		// Never unload the mod while its UI thread might still run.
		if (WaitForSingleObject(g_uiThread, 5000) != WAIT_OBJECT_0) {
			Wh_Log(L"BubbleGlass: UI thread did not exit in time");
			ExitProcess(1);
		}

		CloseHandle(g_uiThread);
		g_uiThread = nullptr;
		g_uiThreadId = 0;
	}

	if (g_uiReadyEvent) {
		CloseHandle(g_uiReadyEvent);
		g_uiReadyEvent = nullptr;
	}

	if (g_gdiplusToken) {

		g_bubbleGdi.reset();

		GdiplusShutdown(g_gdiplusToken);
		g_gdiplusToken = 0;

	}
}

////////////////////////////////////////////////////////////////////////////////
// Windhawk tool mod implementation for mods which don't need to inject to other
// processes or hook other functions. Context:
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process
//
// The mod will load and run in a dedicated windhawk.exe process.
//
// Paste the code below as part of the mod code, and use these callbacks:
// * WhTool_ModInit
// * WhTool_ModSettingsChanged
// * WhTool_ModUninit
//
// Currently, other callbacks are not supported.

bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit() {
    DWORD sessionId;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) &&
        sessionId == 0) {
        return FALSE;
    }

    bool isExcluded = false;
    bool isToolModProcess = false;
    bool isCurrentToolModProcess = false;
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
    if (!argv) {
        Wh_Log(L"CommandLineToArgvW failed");
        return FALSE;
    }

    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-service") == 0 ||
            wcscmp(argv[i], L"-service-start") == 0 ||
            wcscmp(argv[i], L"-service-stop") == 0) {
            isExcluded = true;
            break;
        }
    }

    for (int i = 1; i < argc - 1; i++) {
        if (wcscmp(argv[i], L"-tool-mod") == 0) {
            isToolModProcess = true;
            if (wcscmp(argv[i + 1], WH_MOD_ID) == 0) {
                isCurrentToolModProcess = true;
            }
            break;
        }
    }

    LocalFree(argv);

    if (isExcluded) {
        return FALSE;
    }

    if (isCurrentToolModProcess) {
        g_toolModProcessMutex =
            CreateMutex(nullptr, TRUE, L"windhawk-tool-mod_" WH_MOD_ID);
        if (!g_toolModProcessMutex) {
            Wh_Log(L"CreateMutex failed");
            ExitProcess(1);
        }

        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
            ExitProcess(1);
        }

        if (!WhTool_ModInit()) {
            ExitProcess(1);
        }

        IMAGE_DOS_HEADER* dosHeader =
            (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders =
            (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);

        DWORD entryPointRVA = ntHeaders->OptionalHeader.AddressOfEntryPoint;
        void* entryPoint = (BYTE*)dosHeader + entryPointRVA;

        Wh_SetFunctionHook(entryPoint, (void*)EntryPoint_Hook, nullptr);
        return TRUE;
    }

    if (isToolModProcess) {
        return FALSE;
    }

    g_isToolModProcessLauncher = true;
    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_isToolModProcessLauncher) {
        return;
    }

    WCHAR currentProcessPath[MAX_PATH];
    switch (GetModuleFileName(nullptr, currentProcessPath,
                              ARRAYSIZE(currentProcessPath))) {
        case 0:
        case ARRAYSIZE(currentProcessPath):
            Wh_Log(L"GetModuleFileName failed");
            return;
    }

    WCHAR
    commandLine[MAX_PATH + 2 +
                (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) - 1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath,
               WH_MOD_ID);

    HMODULE kernelModule = GetModuleHandle(L"kernelbase.dll");
    if (!kernelModule) {
        kernelModule = GetModuleHandle(L"kernel32.dll");
        if (!kernelModule) {
            Wh_Log(L"No kernelbase.dll/kernel32.dll");
            return;
        }
    }

    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE hUserToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
        LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles,
        DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory,
        LPSTARTUPINFOW lpStartupInfo,
        LPPROCESS_INFORMATION lpProcessInformation,
        PHANDLE hRestrictedUserToken);
    CreateProcessInternalW_t pCreateProcessInternalW =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule,
                                                 "CreateProcessInternalW");
    if (!pCreateProcessInternalW) {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_FORCEOFFFEEDBACK,
    };
    PROCESS_INFORMATION pi;
    if (!pCreateProcessInternalW(nullptr, currentProcessPath, commandLine,
                                 nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS,
                                 nullptr, nullptr, &si, &pi, nullptr)) {
        Wh_Log(L"CreateProcess failed");
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModUninit();
    ExitProcess(0);
}
