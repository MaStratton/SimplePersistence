cypher-shell -a localhost:7687 -u neo4j -p password "match (e:EMPLOYEE {ID:'$1'}) set e.fName = '$2', e.lName = '$3', e.hireYear = '$4'"
