package main

import (
	"fmt"
	"math/rand"
	"time"
)

type protein struct {
	compound    byte
	hydrophobic bool
	polar       bool
}

func createMatrix(size int) [][]protein {
	var matrix = make([][]protein, size)
	for i := 0; i < size; i++ {
        matrix[i] = make([]protein, size)
		for j := 0; j < size; j++ {
            matrix[i][j].compound = '*'
        }
	}
	return matrix
}

func rnd() int {
	return rand.Intn(12)*2+1;
}

func isEmpty(matrix [][]protein) bool {
    for i := range matrix{
        for j := range matrix[i]{
            if matrix[i][j].compound != '*'{
                return false
            }
        }
    }
    return true       
}

func findCenter(matrix [][]protein) (x int, y int) {
    x = len(matrix)/2
    y = len(matrix[0])/2
    return x,y
}

func appendToClosestElement(matrix [][]protein, p protein) {
    var x, y int
    var originalX int
    if (isEmpty(matrix)){
        x,y = findCenter(matrix)
        matrix[x][y] = p
        return
    }else{
        for i := range matrix{
            for j := range matrix[i]{
                if matrix[i][j].compound != '*'{
                    x = i
                    y = j
                    originalX = i
                }
            }
        }
    }
    
    for {
        x++
        if x >= len(matrix){
            x = originalX
            y++
        }
        if y >= len(matrix[0]){
            break
        }
        if matrix[x][y].compound == '*'{
            matrix[x][y] = p
            break
        }
    }

}

func insert(matrix [][]protein, element protein){
    var x, y int
    if (isEmpty(matrix)){
        x,y = findCenter(matrix)
    }else{
        x = rand.Intn(len(matrix))
        y = rand.Intn(len(matrix[0]))
    }
    matrix[x][y] = element
}

func print(matrix [][]protein){
    for i := range matrix{
        for j := range matrix[i]{
            fmt.Printf("%c ",matrix[i][j].compound)
        }
        fmt.Println("")
    }
}

func main() {
    rand.Seed(time.Now().UnixNano())
	var matrix = createMatrix(rnd())
    fmt.Println("Matrix is empty ",isEmpty(matrix))
    insert(matrix, protein{'A',true,false})
    appendToClosestElement(matrix, protein{'B',true,false})
    appendToClosestElement(matrix, protein{'C',true,false})
    appendToClosestElement(matrix, protein{'D',true,false})
    print(matrix)
}