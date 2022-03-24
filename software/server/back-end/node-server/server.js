const express = require('express')
const dotenv = require('dotenv')
const app = express()
const port = 3000

app.get('/', (req, res) => {
  res.send('Hello World!')
})

app.listen(port, () => {
  console.log(`node-server listening on port ${port}`)
})