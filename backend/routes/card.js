const express = require('express');
const router = express.Router();
const card = require('../models/card_model');
const { checkAdmin } = require('../authentication');

const isCardOwnerOrAdmin = (req, res, next) => {
  if (req.cardnumber === req.params.cardnumber || req.isAdmin) {
    return next();
  }
  return res
    .status(403)
    .send({ error: 'Forbidden. Card owner or admin required.' });
};

/**
 * Get all card details (except pin)
 * Requires admin access
 * @returns {void}
 */
router.get('/', checkAdmin, function (request, response) {
  card.getAll(function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result);
    }
  });
});

/**
 * Only logged in card owner (or admin) can view card data
 * @param {number} number
 * @returns {Object} - Card data
 */
router.get(
  '/bycardnumber/:cardnumber',
  isCardOwnerOrAdmin,
  function (request, response) {
    card.getByCardnumber(request.params.cardnumber, function (err, result) {
      if (err) {
        response.json(err);
      } else {
        response.json(result[0]);
      }
    });
  },
);

/**
 * Get card data by id.
 * for card owner or admin
 */
router.get('/:idcard', checkAdmin, function (request, response) {
  card.getById(request.params.idcard, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result[0]);
    }
  });
});

/**
 * Add new card. Requires admin access
 */
router.post('/', checkAdmin, function (request, response) {
  card.add(request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

/**
 *
 * Updates the card in the database. Requires Admin access
 * Voided parameters will be kept
 * @route PUT /card/:idcard
 * @param {number} idcard - The ID of the card to update (provided in the URL).
 * @param {Object} request.body - The request body containing the updated card data.
 * @param {string} [request.body.cardnumber] - The new card number (optional).
 * @param {string} [request.body.pin] - The new PIN, which will be hashed (optional).
 * @param {string} [request.body.type] - The card type (optional).
 * @param {number} [request.body.idcustomer] - The ID of the customer owning the card (optional).
 * @param {number} [request.body.locked_status] - Locked status (optional).
 * @returns {Object} 401 - Unauthorized. Admin access is required.
 * @returns {Object} 200 - Success. Returns the number of affected rows.
 * @returns {Object} 500 - Internal Server Error. Returns the error details.
 */
router.put('/:idcard', checkAdmin, function (request, response) {
  card.update(request.params.idcard, request.body, function (err, result) {
    if (err) {
      return response.status(500).json(err);
    }

    response.json(result.affectedRows);
  });
});

/**
 *
 * Deletes card. Requires Admin access
 *
 * @route DELETE /card/:idcard
 * @param {number} idcard - The ID of the card to update (provided in the URL).
 * @param {Object} request.body - The request body containing the updated card data.
 * @param {string} [request.body.cardnumber] - The new card number (optional).
 * @param {string} [request.body.pin] - The new PIN, which will be hashed (optional).
 * @param {string} [request.body.type] - The card type (optional).
 * @param {number} [request.body.idcustomer] - The ID of the customer owning the card (optional).
 * @returns {Object} 401 - Unauthorized. Admin access is required.
 * @returns {Object} 200 - Success. Returns the number of affected rows.
 * @returns {Object} 500 - Internal Server Error. Returns the error details.
 */
router.delete('/:idcard', checkAdmin, function (request, response) {
  card.delete(request.params.idcard, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      return response.json(result.affectedRows);
    }
  });
});

module.exports = router;
