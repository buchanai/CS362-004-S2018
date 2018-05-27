CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

#TESTS
randomtestcard1.out: randomtestcard1.c dominion.o rngs.o
	echo "--RANDOM TEST CARD 1--" > randomtestcard1.out
	echo "  Tests being performd on refactored ('buggy') code from assignment 2." >> randomtestcard1.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.c rngs.c $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov dominion.c -b >> randomtestcard1.out
	echo "--SMITHY CARD DOMINION.C.GCOV FILE INFO--" >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: randomtestcard2.c dominion.o rngs.o
	echo "--RANDOM TEST CARD 2--" > randomtestcard2.out
	echo "  Tests being performd on refactored ('buggy') code from assignment 2." >> randomtestcard2.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.c rngs.c $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	echo "--COVERAGE RESULTS--" >> randomtestcard2.out
	gcov dominion.c -b >> randomtestcard2.out
	echo "--VILLAGE CARD DOMINION.C.GCOV FILE INFO--" >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o
	echo "--RANDOM TEST ADVENTURER CARD--" > randomtestadventurer.out
	echo "  Tests being performd on refactored ('buggy') code from assignment 2." >> randomtestadventurer.out
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.c rngs.c $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	echo "--COVERAGE RESULTS--" >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out
	echo "--ADVENTURER CARD DOMINION.C.GCOV FILE INFO--" >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out


#UNIT TESTS
unittestresults.out: unittest1.c unittest2.c unittest3.c cardtest1.c cardtest2.c dominion.o rngs.o
	echo "UNIT TEST RESULTS" > unittestresults.out
	
	echo "---UNIT TESTS---" >> unittestresults.out
	echo "Unit Test 1:" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.c rngs.c $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "Unit Test 2:" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.c rngs.c $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "Unit Test 3:" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.c rngs.c $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "Unit Test 4:" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.c rngs.c $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "---CARD TESTS---" >> unittestresults.out
	gcc -o cardtest1 -g cardtest1.c dominion.c rngs.c $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	gcc -o cardtest2 -g cardtest2.c dominion.c rngs.c $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	gcc -o cardtest3 -g cardtest3.c dominion.c rngs.c $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	gcc -o cardtest4 -g cardtest4.c dominion.c rngs.c $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so testDrawCard *.out testDrawCard.exe cardtest1 cardtest2 unittest1 unittest2 unittest3
