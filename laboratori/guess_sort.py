import random

class SortingAlgorithm:
	def __init__(self, data, verbose = True):
		self.data = data
		self.comparisons = 0
		self.operations = 0
		self.verbose = verbose

	def getData(self):
		return self.data

	def getOperations(self):
		return self.operations

	def getComparisons(self):
		return self.comparisons

	def sort(self):
		raise NotImplementedError
		

class GuessSort(SortingAlgorithm):
	def __isSorted(self):
		return all(self.data[i] <= self.data[i+1] for i in range(len(self.data) - 1))

	def sort(self):
		cycles = 0
		operations = 0
		while True:
			if cycles % 1000000 == 0:
				print(f"Cycle {cycles}")
				if self.__isSorted():
					break
			cycles += 1
			i = random.randint(0, len(self.data) - 1)
			j = random.randint(0, len(self.data) - 1)

			if (((i < j) and self.data[i] > self.data[j]) or ((i > j) and self.data[i] < self.data[j])):
				self.data[i], self.data[j] = self.data[j], self.data[i]
				operations += 1

		print("Sorted by doing {} operations".format(operations))


sorter = GuessSort([3,2,5,6,9,7,4])
sorter.sort()
print(sorter.getData())

inList = []
for i in range(1000):
	inList.append(random.randint(0,50000))

sorter = GuessSort(inList)
sorter.sort()
print('First 20 sorted elements:', sorter.getData()[:20])
