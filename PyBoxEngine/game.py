import display
import graphics
import input
import math

t = 0.0
x = 100.0
y = 100.0
r = 50.0

grasses = []

print("Game start...")

while not display.close_requested():
	# clear screen
	display.clear_screen(1.0, 0.0, 0.5)
	# update variables
	t += 0.1
	x += input.axis_lx()
	y += input.axis_ly()
	r += input.axis_ry()
	# place grasses
	if input.button_down(1):
		grasses.append((x, y))
	# draw sprites
	graphics.draw_sprite("face.png", int(x), int(y))
	graphics.draw_sprite("face.png", int(x + math.cos(t) * r), int(y + math.sin(t) * r))
	# draw grasses
	for grass in grasses:
		graphics.draw_sprite("grass.png", int(grass[0]), int(grass[1]))
	# end frame
	display.post_update()

print("Done!")