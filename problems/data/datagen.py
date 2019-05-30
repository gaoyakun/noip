import random
import time
random.seed (int(time.time()) % 10000)

def gen_nwaymerge (in_filename, out_filename, num_arrays, max_number, min_number, max_size, min_size):
	arr = []
	with open (in_filename, "w") as f:
		f.write ('%d\n' % num_arrays)
		for i in range(num_arrays):
			sz = random.randrange(min_size, max_size)
			l = sorted([random.randint(min_number, max_number) for k in range(sz)])
			f.write ('%d ' % sz)
			f.write ('%s\n' % ' '.join(map(lambda x:str(x), l)))
			arr += l
	arr = sorted(arr)
	with open (out_filename, "w") as f:
		f.write ('%s' % ' '.join(map(lambda x:str(x), arr)))
		
gen_nwaymerge ('nwaymerge1.in', 'nwaymerge1.out', 10, 10, 0, 10, 1)
gen_nwaymerge ('nwaymerge2.in', 'nwaymerge2.out', 100, 100, 0, 100, 1)
gen_nwaymerge ('nwaymerge3.in', 'nwaymerge3.out', 1000, 9999, 0, 1001, 1)
gen_nwaymerge ('nwaymerge4.in', 'nwaymerge4.out', 1600, 9999, 0, 1001, 1)
gen_nwaymerge ('nwaymerge5.in', 'nwaymerge5.out', 1600, 9999, 0, 1001, 1000)


		
