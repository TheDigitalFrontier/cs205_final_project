#include "tree_node.hpp"
#include "datasets.hpp"

// Constructors:

TreeNode::TreeNode(DataFrame dataframe)
{
    /** Build a TreeNode with only splitting attributes. */
    this->parent_ = nullptr;
    this->left_ = nullptr;
    this->right_ = nullptr;
    this->dataframe_ = dataframe;
    //this->split_feature_ = NULL;
    //this->split_threshold_ = NULL;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

TreeNode::TreeNode(DataFrame dataframe, int split_feature, double split_threshold)
{
    /** Build a TreeNode with only a dataframe. */
    this->parent_ = nullptr;
    this->left_ = nullptr;
    this->right_ = nullptr;
    this->dataframe_ = dataframe;
    //this->split_feature_ = NULL;
    //this->split_threshold_ = NULL;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

TreeNode::TreeNode(TreeNode *parent, TreeNode *left, TreeNode *right, DataFrame dataframe, int split_feature, double split_threshold)
{
    /** Build a TreeNode with all attributes. */
    this->parent_ = parent;
    this->left_ = left;
    this->right_ = right;
    this->dataframe_ = dataframe;
    this->split_feature_ = split_feature;
    this->split_threshold_ = split_threshold;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

TreeNode::TreeNode(TreeNode *parent, TreeNode *left, TreeNode *right)
{
    /** Build a TreeNode without splitting attributes. */
    this->parent_ = parent;
    this->left_ = left;
    this->right_ = right;
    //this->dataframe_ = NULL;
    //this->split_feature_ = NULL;
    //this->split_threshold_ = NULL;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

TreeNode::TreeNode()
{
    /** Build a TreeNode with null attributes. */
    this->parent_ = nullptr;
    this->left_ = nullptr;
    this->right_ = nullptr;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

// Getters:

int TreeNode::getSize() const
{
    /**
     * Get number of nodes (including self) in subtree rooted at this node.
     */
    return this->size_;
}

int TreeNode::getHeight() const
{
    /**
     * Get height of subtree rooted at this node.
     */
    return this->height_;
}

int TreeNode::getDepth() const
{
    /** 
     * Get distance between this node and the root (where root has depth zero).
     */
    return this->depth_;
}

TreeNode * TreeNode::getParent() const
{
    /** 
     * Get pointer to parent node.
     */
    return this->parent_;
}

TreeNode * TreeNode::getLeft() const
{
    /** 
     * Get pointer to left child.
     */
    return this->left_;
}

TreeNode * TreeNode::getRight() const
{
    /** 
     * Get pointer to right child.
     */
    return this->right_;
}

DataFrame TreeNode::getDataFrame() const
{
    /** 
     * Get dataframe.
     */
    return this->dataframe_;
}

int TreeNode::getSplitFeature() const
{
    /** 
     * Get index of splitting column.
     */
    return this->split_feature_;
}

double TreeNode::getSplitThreshold() const
{
    /** 
     * Get numberical splitting thresold.
     */
    return this->split_threshold_;
}

// Setters:

void TreeNode::setLeft(TreeNode *left)
{
    /** 
     * Set pointer to left child.
     */
    this->left_ = left;
    left->parent_ = this;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

void TreeNode::setRight(TreeNode *right)
{
    /** 
     * Set pointer to right child.
     */
    this->right_ = right;
    right->parent_ = this;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

void TreeNode::setDataFrame(DataFrame dataframe)
{
    /** 
     * Set dataframe for splitting.
     */
    this->dataframe_ = dataframe;
}

void TreeNode::setSplitFeature(int split_feature)
{
    /** 
     * Set index of splitting column.
     */
    this->split_feature_ = split_feature;
}

void TreeNode::setSplitThreshold(double split_threshold)
{
    /** 
     * Set numberical splitting thresold.
     */
    this->split_threshold_ = split_threshold;
}

// Utilities:

TreeNode * TreeNode::findRoot()
{
    /**
     * Recursively find the the node with no parent.
     */
    TreeNode *root;
    root = this;
    while ( root->parent_ != nullptr )
    {
        root = root->parent_;
    }
    return root;
}

void TreeNode::updateSizes()
{
    /**
     * Helper function for recursively updating node size.
     */
    // Recruse down:
    if (this->left_ != nullptr ){ this->left_->updateSizes(); }
    if (this->right_ != nullptr ){ this->right_->updateSizes(); }
    // Update this node and return:
    this->size_ = 1;
    if ( this->left_ != nullptr ){ this->size_ += this->left_->size_; }
    if ( this->right_ != nullptr ){ this->size_ += this->right_->size_; }
}

void TreeNode::updateHeights()
{
    /**
     * Helper function for recursively updating node size.
     */
    // Recruse down:
    if (this->left_ != nullptr ){ this->left_->updateHeights(); }
    if (this->right_ != nullptr ){ this->right_->updateHeights(); }
    // Update this node and return:
    int left_height;
    int right_height;
    if ( this->left_ != nullptr ){ left_height = this->left_->height_; } else { left_height = 0; }
    if ( this->right_ != nullptr ){ right_height = this->right_->height_; } else { right_height = 0; }
    this->height_ = std::max(left_height,right_height) + 1;
}

void TreeNode::updateDepths()
{
    /**
     * Helper function for recursively updating node size.
     */
    // Update this node:
    int d;
    if ( this->parent_ != nullptr ){ d = this->parent_->depth_ + 1; } else { d = 0; }
    this->depth_ = d;
    // Recruse down:
    if (this->left_ != nullptr ){ this->left_->updateDepths(); }
    if (this->right_ != nullptr ){ this->right_->updateDepths(); }
}



std::vector<TreeNode*> TreeNode::findLeaves()
{
    /**
     * Get leaves in subtree rooted at this node.
     */
    std::vector<TreeNode*> results;
    return this->findLeaves(results);
}

std::vector<TreeNode*> TreeNode::findLeaves(std::vector<TreeNode*> results)
{
    /**
     * Get leaves in subtree rooted at this node: recursive helper for getLeaves().
     */
    // If this is a leaf, add to results:
    if ((this->left_ == nullptr) and (this->right_ == nullptr)){ results.push_back(this); }
    // (Otherwise): Recurse downward.
    if (this->left_ != nullptr){ results = this->left_->findLeaves(results); }
    if (this->right_ != nullptr){ results = this->right_->findLeaves(results); }
    return results;
}
