package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"strings"

	"github.com/gorilla/handlers"
	"github.com/gorilla/mux"
)

type ComandoI struct {
	Exp string `json:exp`
}

type ContData struct {
	Usuario string `json:usuario`
	Clave   string `json:clave`
	Id      string `json:id`
}

type DatoRe struct {
	Validate  bool   `json:validate`
	Contenido string `json:contenido`
}
type DatoRepIMG struct {
	Validate  bool   `json:validate`
	Contenido string `json:contenido`
	Datob64   string `json:datob64`
}

func AnalisisContenido(contenido string) {

	lineacomando := "" // donde se guarda el primer comando
	//contador := 0      //contador general para recorrer el comando
	comandosep := strings.Split(contenido, "") //c o m a n do

	fmt.Println("El tamaño total del arreglo creado", len(comandosep))
	//fmt.Println("Contenido del arreglo", comandosep)

	for i := 0; i < len(comandosep); i++ {
		//fmt.Println("v: ", comandosep[i])

		if strings.Compare(comandosep[i], "\n") == 0 {
			fmt.Println("Se genera el comando para el analisis: ", lineacomando)
			lineacomando += (comandosep[i])
			AnalizadorComando(lineacomando)
			lineacomando = "" //receteo la linea del comando
		} else if i == (len(comandosep) - 1) {
			lineacomando += (comandosep[i])
			fmt.Println("Se genera el comando para el analisis: ", lineacomando)
			AnalizadorComando(lineacomando)

		} else {
			lineacomando += (comandosep[i]) ///le cambie el tolower
		}

	}

}
func AnalisisCadena(w http.ResponseWriter, r *http.Request) {

	var nweT ComandoI
	var respuesta DatoRe
	reqBoy, err := ioutil.ReadAll(r.Body)

	if err != nil { //si hay errores
		fmt.Fprintf(w, "inserte datos Validos")

	}
	json.Unmarshal(reqBoy, &nweT)

	fmt.Println("Iformacion: ", nweT.Exp)
	AnalisisContenido(nweT.Exp)

	fmt.Println("----------------------------------------")
	//Aqui mando una respuesta al front
	respuesta.Validate = true
	respuesta.Contenido = cadenaf
	cadenaf = ""
	//fmt.Println("Lo generado : ")
	//fmt.Println(cadenaf)
	w.Header().Set("Content-Type", "application/json") //tipo de dato
	json.NewEncoder(w).Encode(respuesta)               //solicito el dato agregado

}

//para retornar la imagen base64:

func analissisRepb64(w http.ResponseWriter, r *http.Request) {

	var nweT ComandoI
	var respuesta DatoRepIMG
	reqBoy, err := ioutil.ReadAll(r.Body)

	if err != nil { //si hay errores
		fmt.Fprintf(w, "inserte datos Validos")

	}
	json.Unmarshal(reqBoy, &nweT)

	fmt.Println("Iformacion: ", nweT.Exp)
	AnalisisContenido(nweT.Exp)

	fmt.Println("----------------------------------------")
	//Aqui mando una respuesta al front
	respuesta.Validate = repVali
	respuesta.Contenido = cadenaf
	respuesta.Datob64 = imagenFinalRep
	cadenaf = ""
	imagenFinalRep = "" //limpio la variable
	repVali = false     //aqui lo regreso a false
	//fmt.Println("Lo generado : ")
	//fmt.Println(cadenaf)
	w.Header().Set("Content-Type", "application/json") //tipo de dato
	json.NewEncoder(w).Encode(respuesta)               //solicito el dato agregado

}

func valiLogin(w http.ResponseWriter, r *http.Request) {
	var nweT ContData
	var respuesta DatoRe
	reqBoy, err := ioutil.ReadAll(r.Body)

	if err != nil { //si hay errores
		fmt.Fprintf(w, "inserte datos Validos")

	}
	json.Unmarshal(reqBoy, &nweT)

	fmt.Println("Iformacion: ", nweT.Usuario)
	fmt.Println("Iformacion: ", nweT.Clave)
	fmt.Println("Iformacion: ", nweT.Id)
	fmt.Println("----------------------------------------")
	respuesta.Validate = valMontado(nweT.Id)
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(respuesta) //solicito el dato agregado

}
func main() {

	fmt.Println("Hola Perros")

	router := mux.NewRouter()

	//****
	headers := handlers.AllowedHeaders([]string{"X-Requested-With", "Content-Type", "Authorization"})
	methods := handlers.AllowedMethods([]string{"GET", "POST", "PUT", "HEAD", "OPTIONS"})
	origins := handlers.AllowedOrigins([]string{"*"})
	router.HandleFunc("/login", valiLogin).Methods("POST")
	router.HandleFunc("/Comandos", AnalisisCadena).Methods("POST")
	router.HandleFunc("/reportes", analissisRepb64).Methods("POST")
	log.Fatal(http.ListenAndServe(":3000", handlers.CORS(headers, methods, origins)(router)))

	///ENABLECORS lo estoy agregando
	/*router.Use(corsMiddleware)
	router.HandleFunc("/comando", AnalisisCadena).Methods("POST")
	router.HandleFunc("/login", valiLogin).Methods("POST")

	log.Fatal(http.ListenAndServe(":3000", router))*/

}
