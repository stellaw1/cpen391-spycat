const express = require('express')
const router = express.Router()
const User = require('../models/user')

// GET all
router.get('/', async (req, res) => {
    try {
        const users = await User.find()
        res.json(users)
    } catch (err) {
        res.status(500).json({message: err.message})
    }
})

// GET one
// router.get('/:id')


// POST one
router.post('/', async (req, res) => {
    const user = new User({
        id: req.body.id,
        pet_colour: req.body.pet_colour,
        friendship_points: 0
    })
    try {
        const newUser = await user.save()
        res.status(201).json(newUser)
    } catch (err) {
        res.status(400).json({message: err.message})
    }
})

module.exports = router