all:
	gcc transferData.c -o transferData
	gcc transferData2.c -o transferData2
clean:
	rm -f A.csv B.csv C.csv D.csv E.csv F.csv G.csv H.csv
	rm -f *尿.csv *水.csv
	rm -f transferData transferData2
