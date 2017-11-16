package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"strconv"
)

type girl struct {
	Name    string
	Country string
	Age     int
}

func main() {
	//STRINGS
	http.HandleFunc("/a", func(res http.ResponseWriter, req *http.Request) {
		if req.Method == "POST" {
			bodyTemp, _ := ioutil.ReadAll(req.Body)
			fmt.Println(string(bodyTemp))
		}
	})
	http.HandleFunc("/b", func(res http.ResponseWriter, req *http.Request) {
		if req.Method == "POST" {
			res.Write([]byte("GOLANG"))
		}
	})
	//JSON
	http.HandleFunc("/c", func(res http.ResponseWriter, req *http.Request) {
		if req.Method == "POST" {
			var girlTemp girl
			json.NewDecoder(req.Body).Decode(&girlTemp)
			fmt.Println(girlTemp.Name)
			fmt.Println(girlTemp.Country)
			fmt.Println(strconv.Itoa(girlTemp.Age))
		}
	})
	http.HandleFunc("/d", func(res http.ResponseWriter, req *http.Request) {
		res.Header().Set("Content-Type", "application/json")
		if req.Method == "POST" {
			json.NewEncoder(res).Encode(&girl{Name: "Nuria", Country: "Spain", Age: 40})
		}
	})

	http.ListenAndServe(":8080", nil)
}
