const express = require('express')
const router = express.Router()

module.exports = router

// GET all
router.get('/', (req, res) => {
    res.send('test')
})