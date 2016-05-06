import os



[os.rename(f, f.replace('txt', 'doc')) for f in os.listdir('.') if not f.startswith('.')]
