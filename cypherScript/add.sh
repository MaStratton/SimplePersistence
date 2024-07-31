cypher-shell -a localhost:7687 -u neo4j -p password "CREATE ($2:EMPLOYEE{ID:'$1', fName:'$2', lName: '$3', hireYear: '$4' })"
