const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');
const card = require('../models/card_model');

router.post('/', function (req, res) {
  if (!req.body.cardnumber || !req.body.pin) {
    console.log('username or password missing');
    res.send(401);
    return;
  }
  const cardnum = req.body.cardnumber;
  const pin = req.body.pin;

  card.checkPassword(cardnum, (dbError, dbResult) => {
    if (dbError) {
      res.send(500);
      return;
    }
    if (!dbResult.length) {
      // res.sendStatus(500);
      res.send(`Card number doesn't exist`);
      return;
    }

    bcrypt.compare(pin, dbResult[0].pin, (err, compareResult) => {
      if (compareResult) {
        const token = generateAccessToken({ cardnumber: cardnum });
        res.send({ token });
      } else {
        res.sendStatus(401);
      }
    });
  });
});

function generateAccessToken(cardnumber) {
  dotenv.config();
  return jwt.sign(cardnumber, process.env.JWT_TOKEN, { expiresIn: '1800s' });
}

module.exports = router;
