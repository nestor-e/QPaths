

def buildGraph(adjFile):
	f = open(adjFile, 'r')
	row = 0
	grid = []
	for line in f:
		grid.append([])
		for term in line.split(','):
			grid[row].append(term.strip())
		row += 1
	f.close()
	return grid

def rFill(grid, x, y):
	if x < 0 or x >= len(grid[0]) or y < 0 or y >= len(grid):
		return
	str = grid[y][x]
	if str == '-1':
		return
	else:
		grid[y][x] = '-1'
		if(str[0] == 'y'):
			rFill(grid, x-1, y)
		if(str[1] == 'y'):
			rFill(grid, x+1, y)
		if(str[2] == 'y'):
			rFill(grid, x, y-1)
		if(str[3] == 'y'):
			rFill(grid, x, y+1)
	
	
def checkConnected(grid):
	fill = grid[:]
	for i in range(len(fill)):
		fill[i] = fill[i][:]
	rFill(fill, 0, 0)
	for row in fill:
		for cel in row:
			if cel != '-1':
				return False
	return True

def checkUndirected(grid):
	rows = len(grid)
	cols = len(grid[0])
	print(rows,'x',cols)
	valid  = True
	for x in range(cols):
		for y in range(rows):
			str = grid[y][x]
			if str != '-1':
				if(str[0] == 'y'):
					if x == 0 or grid[y][x-1] == '-1' or grid[y][x-1][1] != 'y' : 
						print((x,y), ':', str, '->' , (x-1, y), ':',grid[y][x-1])
						valid = False 
				if(str[1] == 'y'):
					if x == cols - 1 or grid[y][x+1] == '-1' or grid[y][x+1][0] != 'y' : 
						print((x,y), ':', str, '->' , (x+1, y), ':',grid[y][x+1])
						valid = False	
				if(str[2] == 'y'):
					if y == 0 or grid[y-1][x] == '-1' or grid[y-1][x][3] != 'y' : 
						print((x,y), ':', str, '->' , (x, y-1), ':',grid[y-1][x])
						valid = False
				if(str[3] == 'y'):
					if y == rows - 1 or grid[y+1][x] == '-1' or grid[y+1][x][2] != 'y' : 
						print((x,y), ':', str, '->' , (x, y+1), ':',grid[y+1][x])
						valid = False
						
	return valid
	
	
def main(fileName):
	g = buildGraph(fileName)
	print( checkConnected(g) )
	print( checkUndirected(g) )

if __name__ == "__main__":
	main("connections.csv")