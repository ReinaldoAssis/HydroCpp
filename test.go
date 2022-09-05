package main

import (
	"fmt"
	"math/rand"
	"time"
)

type vector2 struct{
    x int
    y int
}

type aminoacid struct {
    compound byte
    polarity bool
    position vector2
}

type protein struct{
    matrix [][]aminoacid
    constraint vector2
    size vector2
}

func (p *protein) instanciateMatrix(size int) {
    p.matrix = make([][]aminoacid, size)
    p.size = vector2{size,size}
    p.constraint = vector2{-1,-1}

    for i := 0; i<size; i++{
        p.matrix[i] = make([]aminoacid, size)
        for j := 0; j<size; j++{
            p.matrix[i][j] = aminoacid{'*',false,vector2{i,j}}
        }
    }
}

func (p protein) printMatrix() {
    for i:=0; i<len(p.matrix); i++ {
        for j:=0; j<len(p.matrix); j++ {
            fmt.Printf("%c ", p.matrix[i][j].compound)
        }
        fmt.Println()
    }
}

func (p *protein) append(start vector2, sequence []aminoacid){
    pos := start
    for i := range sequence {
        if pos.y >= p.size.y {
            fmt.Println("[error] matrix overflow.")
            return
        }
        p.matrix[pos.y][pos.x] = sequence[i]
        pos.x++
        if p.constraint.x != -1{
            if pos.x +1 > len(p.matrix[0])-(p.constraint.x){
                pos.x = start.x
                pos.y++
            }
        } else if pos.x +1 > len(p.matrix[0]){
                pos.x = start.x
                pos.y++
        }

        
    }
}


func (p protein) center() vector2{
    return vector2{len(p.matrix)/2, len(p.matrix)/2}
}

//======================

func readAminoacidSequence() []aminoacid {
    var sequence []aminoacid = make([]aminoacid, 0)
    var aminoacid aminoacid
    for {
        fmt.Scanf("%c", &aminoacid.compound)
        if aminoacid.compound == '!'{
            break
        }
        sequence = append(sequence, aminoacid)
    }
    return sequence
}

func randomSequence() []aminoacid{
    var size int = rand.Intn(20)*2+5
    var sequence []aminoacid = make([]aminoacid,size)
    for i:=0; i<size; i++{
        var compound byte
        if rand.Intn(100) < 50 {
            compound = 'P'
        } else {
            compound = 'H'
        }
        sequence[i] = aminoacid{compound,compound == 'H',vector2{-1,-1}}
    }
    return sequence
}

func main(){

    rand.Seed(time.Now().UnixNano())

    var space protein
    space.instanciateMatrix(10)
    space.constraint = vector2{3,0}
    space.append(vector2{3,0},randomSequence())
    space.printMatrix()

}