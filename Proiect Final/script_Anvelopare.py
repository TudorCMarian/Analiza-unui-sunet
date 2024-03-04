import numpy as np
from scipy.signal import hilbert

from scipy.io import wavfile
samplerate, data = wavfile.read('Wav52.wav')
signal = data
analytic_signal = hilbert(signal)
amplitude_envelope = np.abs(analytic_signal)
wavFileInfo = open("envelopeInfo.txt", "a")
wavFileInfo.write(str(amplitude_envelope.size)+'\n')
wavFileInfo.close()

print(amplitude_envelope)
print(amplitude_envelope.size)


np.savetxt("envelopeData.txt", amplitude_envelope, fmt="%9.9f")