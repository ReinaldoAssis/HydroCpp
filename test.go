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

type VectorSlice []vector2

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

func negativeRnd() int {
    if rand.Intn(2) == 0{
         return -1
    } else{
        return 1
    }
}

func negativeDelta() vector2{
    if rand.Intn(2) == 0{
        return vector2{negativeRnd(),0}
    } else{
        return vector2{0,negativeRnd()}
    }
}

func (s VectorSlice) contains(vec vector2) bool{
    for _, a := range s{
        if a == vec{
            return true
        }
    }
    return false
}

func (vec vector2) restrains(vetores VectorSlice) bool{
    for i := range vetores{
        if vec.x < vetores[i].x || vec.y < vetores[i].y{
            return false
        }
    }
    return true
}

func (p *protein) append(start vector2, sequence []aminoacid){
    pos := start
    for i := range sequence {

        var delta vector2 = negativeDelta()

        if pos.y >= p.size.y {
            fmt.Println("[error] matrix overflow.")
            return
        }

        if pos.x+delta.x == -1{
            delta.x = 0
        }

        if pos.y+delta.y == -1{
            delta.y = 0
        }

        //p.matrix[pos.y][pos.x] = sequence[i]
        //pos.x++
        // if p.constraint.x != -1{
        //     if pos.x +1 > len(p.matrix[0])-(p.constraint.x){
        //         pos.x = start.x
        //         pos.y++
        //     }
        // } else if pos.x +1 > len(p.matrix[0]){
        //         pos.x = start.x
        //         pos.y++
        // }

        if p.constraint.x != -1 && p.constraint.y != -1{

            var limit vector2 = vector2{len(p.matrix[0])-(p.constraint.x),len(p.matrix)-(p.constraint.y)}

           // if pos.x + delta.x < limit.x && pos.y + delta.y < limit.y{
                var combinacoes VectorSlice = make([]vector2,4)
                for j:=0; j<4; j++{
                    combinacoes = append(combinacoes, delta)

                if limit.restrains(VectorSlice{{pos.x+delta.x,pos.y},{pos.x,pos.y+delta.y}}){
                    if p.matrix[pos.y+delta.y][pos.x+delta.x].compound == '*'{
                        p.matrix[pos.y+delta.y][pos.x+delta.x] = sequence[i]
                        pos.x++
                        break
                    }else{
                        //se o espaço não estiver disponível, tentar outro
                        delta = negativeDelta()
                        for{
                            if pos.x+delta.x == -1{
                                delta.x = 0
                            }
                    
                            if pos.y+delta.y == -1{
                                delta.y = 0
                            }
                            if len(combinacoes) == 4{
                                break
                            }
                            if (!combinacoes.contains(delta)){
                                break
                            }
                            delta = negativeDelta()
                        }
                    }
                } else{
                    delta = negativeDelta()
                        for{
                            if pos.x+delta.x == -1{
                                delta.x = 0
                            }
                    
                            if pos.y+delta.y == -1{
                                delta.y = 0
                            }
                            if len(combinacoes) == 4{
                                break
                            }
                            if (!combinacoes.contains(delta)){
                                break
                            }
                            delta = negativeDelta()
                        }
                }
            }
           // } 

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
    //matrix padding
    space.constraint = vector2{0,0}
    space.append(vector2{3,4},randomSequence())
    space.printMatrix()

}