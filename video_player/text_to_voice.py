from gtts import gTTS
import os, sys, subprocess, time

class Text():
	def __init__(self, input_text = "Hello World", filename = 'test_voice.mp3'):
		self.voice_file = filename
		self.text = input_text

		tts = gTTS(self.text, lang = 'en')
		tts.save(self.voice_file)

	def speak(self):
		p = subprocess.Popen(['cvlc', self.voice_file])
		time.sleep(4)
		p.terminate()

if __name__ == '__main__':
	txt = Text("Hello, hi there!")
	txt.speak()
