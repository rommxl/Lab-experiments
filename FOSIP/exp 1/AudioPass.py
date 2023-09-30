# %% [markdown]
# # Low Pass Filter

# %% [markdown]
# Importing the required libraries

# %%
import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as signal
import scipy.io.wavfile as wavfile
import sounddevice as sd
import warnings

# %% [markdown]
# Filtering Warnings

# %%
warnings.filterwarnings('ignore')

# %% [markdown]
# Loading the audio file in signal and sampling rate

# %%
fs, x = wavfile.read('./Audio/sample_with_noise.wav')
print('Sampling rate: ', fs)
print('Number of samples: ', x.shape[0])


# %% [markdown]
# Adding the noise to the signal

# %%
noise = np.random.normal(0, 1, x.shape)
x = x + noise

# %% [markdown]
# Playing the noisy signal

# %%
print("Playing the original signal with noise...")
sd.play(x, fs)
sd.wait()

# %% [markdown]
# Save the noisy signal

# %%
wavfile.write('./Audio/sample_with_noise.wav', fs, x.astype(np.int16))

# %% [markdown]
# Declaring the filter parameters

# %%
Fpass = 4000.0  
Fstop = 6000.0  
Fs = 44000.0    
N = 101         

# %% [markdown]
# Making the impulse response of the filter

# %%
h = signal.remez(N, [0, Fpass, Fstop, 0.5 * Fs], [1, 0], Hz=Fs)


# %% [markdown]
# Performing Convolution of the signal and the impulse response

# %%
y = signal.lfilter(h, 1, x)

# %% [markdown]
# Playing the filtered signal

# %%
print("Playing the filtered signal...")
sd.play(y, fs)
sd.wait() 

# %% [markdown]
# Save the filtered signal

# %%
wavfile.write('./Audio/sample_filtered.wav', fs, y.astype(np.int16))


