# ParallelAssignment1
 Parallelizing Sieve of Eratosthenes

main.cpp and outputs folder are necessary. To compile and file location: g++ main.cpp -fopenmp
To run: ./a.out 		// or whatever you want to name it //
This will place its outputs in a document named primes.txt in the outputs folder.
<top ten maximum primes, listed in order from lowest to highest>
<sum of all primes found>
<total number of primes found>
<execution time> 		// specifically from when the threads are spawned to the end of the computations.

In order to produce an efficient method of producing primes, I used the Sieve of Eratosthenes (which I learned about through 2 main sources:
																							https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
																							https://www.massey.ac.nz/~mjjohnso/notes/59735/seminars/01077635.pdf
This sieve is able to produce accurate primes farm more quickly than a brute force method. The primary attributes of this sieve involve:
	All numbers, from 2(the smallest prime) to the maximum number, are initially set to be prime.
	It then sifts out the composite numbers by first marking all multipes of 2 until it reaches the maximum number.
	It then does the same for the next unmarked number.
	By the time it is over, only primes are left unmarked.
	
After this marking, it is easy to output the primes, sum them up, and count them.
After setting the threadcount to 8, the openmp library is used to more evenly distribute the workload between the threads during intensive loops.
As the loop for determining as great varience for runtime, dynamic scheduling was used instead of static.

Testing on my machine provided runtimes under 1.5 seconds for 10^8 numbers. Sample output from my machine can be seen in samplePrimes.txt within the outputs folder.
Eustis was also used to test. Runtime was slightly longer than my own.
Also tested was numbers far less and more than the requisit 10^8.

