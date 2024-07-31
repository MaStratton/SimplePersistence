cypher-shell -a localhost:7687 -u neo4j -p password "match (e:EMPLOYEE {ID:'100000'}) return e.ID as ID, e.fName as First_Name, e.lName as Last_Name, e.hireYear as Hire_Year"
