import pygame
import random
import time
import numpy as np

pygame.init()
pygame.mixer.init()

WIDTH, HEIGHT = 800, 600
BAR_WIDTH = 2
NUM_BARS = WIDTH // BAR_WIDTH
FREQ_BASE = 220  # Hz
FREQ_RANGE = 1760  # Range of frequencies used

def generate_tone(freq, duration, sample_rate=44100):
    t = np.linspace(0, duration, int(sample_rate * duration), False)
    tone = np.sin(freq * t * 2 * np.pi)

    # Add envelope (fade in/out)
    fade_time = int(sample_rate * 0.01)
    envelope = np.ones_like(tone)
    envelope[:fade_time] *= np.linspace(0, 1, fade_time)
    envelope[-fade_time:] *= np.linspace(1, 0, fade_time)
    return tone * envelope

def generate_rich_tone(freq, duration, sample_rate=44100):
    t = np.linspace(0, duration, int(sample_rate * duration), False)
    
    # Add harmonics with different amplitudes
    tone = (
        1 * np.sin(2 * np.pi * freq * t) +       # fundamental
        0.5 * np.sin(2 * np.pi * freq * 2 * t) +   # 2nd harmonic
        0.25 * np.sin(2 * np.pi * freq * 3 * t) +  # 3rd harmonic
        0.125 * np.sin(2 * np.pi * freq * 4 * t) +  # 4th harmonic
        0.0625 * np.sin(2 * np.pi * freq * 5 * t) +   # 5th harmonic
        0.03125 * np.sin(2 * np.pi * freq * 6 * t)   # 5th harmonic
    )
    
    # Envelope for fade in/out
    fade_time = int(sample_rate * 0.01)
    envelope = np.ones_like(tone)
    envelope[:fade_time] *= np.linspace(0, 1, fade_time)
    envelope[-fade_time:] *= np.linspace(1, 0, fade_time)

    return tone * envelope

# C major scale in Hz, 2 octaves
# NOTES = [261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88,
        #  523.25, 587.33, 659.25, 698.46, 783.99, 880.00]

# NOTES = [130.81, 164.81, 196.00,
#         261.63, 329.63, 392.00,
#         523.25, 659.25, 783.99,
#         1046.50]

# JAZZ_NOTES = [
#     130.81, 164.81, 196.00, 246.94,     # C3, E3, G3, B3
#     261.63, 329.63, 392.00, 493.88,     # C4, E4, G4, B4
#     523.25, 659.25, 783.99, 987.77      # C5, E5, G5, B5
# ]
# NOTES = JAZZ_NOTES

def generate_scale(base_freq, intervals, octaves=1):
    scale = [base_freq]
    for _ in range(octaves):
        for interval in intervals:
            next_freq = scale[-1] * 2 ** (interval / 12)
            scale.append(next_freq)
    return scale

major_intervals = [2, 2, 1, 2, 2, 2, 1]  # W W H W W W H
harmonic_minor_intervals = [2, 1, 2, 2, 1, 3, 2]
pentatonic_major_intervals = [2, 2, 3, 2, 3]
major_triad_intervals = [4, 3, 5]
blues_intervals = [3, 2, 1, 1, 3, 2]
japanese_intervals = [1, 4, 2, 1, 4]

C2_FREQ = 65.40639132514966
C3_FREQ = C2_FREQ * 2
C4_FREQ = C3_FREQ * 2
OCTAVE = 4
C_MAJOR = generate_scale(C2_FREQ, major_intervals, octaves=OCTAVE)
C_HARMONIC_MINOR = generate_scale(C2_FREQ, harmonic_minor_intervals, octaves=OCTAVE)
C_PENTATONIC_MAJOR = generate_scale(C2_FREQ, pentatonic_major_intervals, octaves=OCTAVE)
C_MAJOR_TRIAD = generate_scale(C2_FREQ, major_triad_intervals, octaves=OCTAVE)
C_BLUES = generate_scale(C4_FREQ, blues_intervals, octaves=1)  # I don't know if it's major or minor
C_JAPANESE = generate_scale(C2_FREQ, japanese_intervals, 4)  # I don't know the actual name

NOTES = C_MAJOR

def value_to_note(val, max_val):
    idx = int((val / max_val) * len(NOTES))
    idx = min(idx, len(NOTES) - 1)
    return NOTES[idx]

def play_tone(frequency, duration=0.05, volume=0.5):
    sample_rate = 44100
    n_samples = int(round(duration * sample_rate))
    buf = np.sin(2 * np.pi * np.arange(n_samples) * frequency / sample_rate).astype(np.float32)

    # Convert to stereo: duplicate for 2 channels
    stereo_buf = np.column_stack((buf, buf))  # shape = (n_samples, 2)

    sound = pygame.sndarray.make_sound((stereo_buf * (2**15 - 1)).astype(np.int16))
    sound.set_volume(volume)
    sound.play()

def play_note(note_freq, duration=0.08, volume=0.4):
    sample_rate = 44100
    tone = generate_rich_tone(note_freq, duration, sample_rate)

    # Stereo
    stereo = np.column_stack((tone, tone * 0.98))
    sound = pygame.sndarray.make_sound((stereo * (2**15 - 1)).astype(np.int16))
    sound.set_volume(volume)
    sound.play()

def draw_array(arr, color_indices=None):
    screen.fill((0, 0, 0))
    for i, val in enumerate(arr):
        color = (255, 255, 255)
        if color_indices and i in color_indices:
            color = (255, 0, 0)
        pygame.draw.rect(screen, color, (i * BAR_WIDTH, HEIGHT - val, BAR_WIDTH, val))
    pygame.display.flip()

def visual_binary_insertion_sort(arr):
    for i in range(1, len(arr)):
        l, r = 0, i
        while l < r:
            m = (l + r) // 2
            if arr[m] > arr[i]:
                r = m
            else:
                l = m + 1
            # Play tone for comparison
            note = value_to_note(arr[m], HEIGHT)
            # duration = 0.1
            # play_note(note, duration=duration)
            # pygame.time.delay(round(duration * 1000))

        val = arr.pop(i)
        arr.insert(l, val)

        # Play insertion sound
        note = value_to_note(val, HEIGHT)
        duration = random.choice((0.1, 0.2, 0.4, 0.8))
        play_note(note, duration=duration)

        draw_array(arr, color_indices={l})
        pygame.time.delay(round(duration * 1000))
        


screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Sound Sorting")
clock = pygame.time.Clock()

arr = [random.randint(1, HEIGHT) for _ in range(NUM_BARS)]
draw_array(arr)

done = False
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    if not done:
        visual_binary_insertion_sort(arr)
        done = True
        draw_array(arr)
    
    clock.tick(5)

pygame.quit()
