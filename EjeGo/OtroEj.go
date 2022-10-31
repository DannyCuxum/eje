package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
)

type Eje struct {
	ID      int    `json:ID`
	Name    string `json:Name`
	Content string `json:Content`
}

type mues []Eje

var eje = mues{
	{

		ID:      1,
		Name:    "UNA T",
		Content: "contenido",
	},
}

func getMue(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json") //aqui aseignamos los Headers
	json.NewEncoder(w).Encode(eje)                     //aqui mando la informacion tipo json

}
func setMuestra(w http.ResponseWriter, r *http.Request) {
	//recibo la informacion
	var nweT2 Eje
	reqBoy, err := ioutil.ReadAll(r.Body) //leemos el cuerpo del body

	if err != nil { //si hay errores
		fmt.Fprintf(w, "inserte datos Validos")

	}
	//escribo la informacion
	json.Unmarshal(reqBoy, &nweT2) //pase lo que guarde en la lectura en una varible que pueda manipular
	nweT2.ID = len(eje) + 1        //Manipulo la informacion
	eje = append(eje, nweT2)       //Ya lo meto a la lista de tareas

	fmt.Println("ID De la tarea ingresada es: ", nweT2.ID)
	fmt.Println("La tarea ingresada es: ", nweT2.Name)
	fmt.Println("Contenido de la tarea ingresada es: ", nweT2.Content)

}

func conec() {
	fmt.Println("si se logro conectar al server..")

}

/*

package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"

	"github.com/gorilla/mux"
)

type task struct {
	ID      int    `json:ID`
	Name    string `json:Name`
	Content string `json:Content`
}

type ComandoI struct {
	expresion string `json:expresion`
}

type alltasks []task

var tasks = alltasks{
	{

		ID:      1,
		Name:    "UNA T",
		Content: "contenido",
	},
}

func getTasks(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json") //aqui aseignamos los Headers
	json.NewEncoder(w).Encode(tasks)                   //aqui mando la informacion tipo json

}
func AnalisisComandos(w http.ResponseWriter, r *http.Request) {

	var nweT ComandoI
	reqBoy, err := ioutil.ReadAll(r.Body)

	if err != nil { //si hay errores
		fmt.Fprintf(w, "inserte datos Validos")

	}
	json.Unmarshal(reqBoy, &nweT)

	fmt.Println("Iformacion: ", nweT.expresion)

}
func setTasks(w http.ResponseWriter, r *http.Request) {
	//recibo la informacion
	var nweT task
	reqBoy, err := ioutil.ReadAll(r.Body) //leemos el cuerpo del body

	if err != nil { //si hay errores
		fmt.Fprintf(w, "inserte datos Validos")

	}
	//escribo la informacion
	json.Unmarshal(reqBoy, &nweT) //pase lo que guarde en la lectura en una varible que pueda manipular
	nweT.ID = len(tasks) + 1      //Manipulo la informacion
	tasks = append(tasks, nweT)   //Ya lo meto a la lista de tareas

	fmt.Println("ID De la tarea ingresada es: ", nweT.ID)
	fmt.Println("La tarea ingresada es: ", nweT.Name)
	fmt.Println("Contenido de la tarea ingresada es: ", nweT.Content)
	//Aqui mando una respuesta
	//w.Header().Set("Content-Type", "application/json") //tipo de dato
	//w.WriteHeader(http.StatusCreated)                  //si fue correcto
	//json.NewEncoder(w).Encode(nweT)                    //solicito el dato agregado

}

func indexru(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Bienbenidos")
}

func main() {

	fmt.Println("Hola Perros")
	//http.HandleFunc("/", index)

	//http.ListenAndServe(":5000", nil)

	router := mux.NewRouter().StrictSlash(true) //Validacion stricta de tipo de acceso

	router.HandleFunc("/", indexru) //si se accede aqui solo muestra el bienvenidos

	router.HandleFunc("/tasks", getMue).Methods("GET") //Metodo Get
	//router.HandleFunc("/tasks", setMuestra).Methods("POST")

	router.HandleFunc("/comando", AnalisisComandos).Methods("POST") //Esto ya va enfocado al Proyecto

	log.Fatal(http.ListenAndServe(":5000", router))
	//conec()
}


*/
