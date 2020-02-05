# traffic_light.py
import time
import sys

currentTime = 0
targetTime = time.time()
currentPositionInPattern = 0
colorPosition = 0
currentState = [ False, False, False ]
basicPattern = [ 5, 0, 0.5, 0.5, 0.5, 0, 5, 0 ]
COLORS = [ 'red', 'yellow', 'green' ]

currentPattern = basicPattern
currentState[colorPosition] = True
targetTime = targetTime + currentPattern[currentPositionInPattern]

done = False
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

    print COLORS[colorPosition] + str(currentState[colorPosition] )

