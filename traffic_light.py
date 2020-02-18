# traffic_light.py
import time
from colorama import init, Fore, Back, Style

currentTime = 0
targetTime = time.time() - 1
currentPositionInPattern = 0
colorPosition = 0
currentState = [ False, False, False ]
basicPattern = [ 5, 0.3, 0.3, 0, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0, 5, 0 ]
COLORS = [ 'red', 'yellow', 'green' ]

currentPattern = basicPattern
currentState[colorPosition] = True
done = False

init()

while not done:
  currentTime = time.time()
  if currentTime > targetTime:

    currentPositionInPattern = currentPositionInPattern + 1
    if currentPositionInPattern > len(currentPattern) - 1:
      currentPositionInPattern = 0
    nextTarget = currentPattern[currentPositionInPattern]

    if nextTarget is 0:
      currentState[colorPosition] = False
      colorPosition = colorPosition + 1

      if colorPosition > 2:
        colorPosition = 0
      continue

    currentState[colorPosition] = not currentState[colorPosition]

    targetTime = targetTime + nextTarget

    red = Fore.RED
    if colorPosition is 0 and currentState[colorPosition]:
      red = red + Back.RED
    else:
      red = red + Back.BLACK

    red = red + 'red' + Style.RESET_ALL


    yellow = red + Fore.YELLOW
    if colorPosition is 1 and currentState[colorPosition]:
      yellow = yellow + Back.YELLOW
    else:
      yellow = yellow + Back.BLACK

    yellow = yellow + 'yellow' + Style.RESET_ALL


    green = yellow + Fore.GREEN
    if colorPosition is 2 and currentState[colorPosition]:
      green = green + Back.GREEN
    else:
      green = green + Back.BLACK

    green = green + 'green' + Style.RESET_ALL

    print(green)
